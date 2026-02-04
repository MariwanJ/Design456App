# NanoVG fork – Review de motor y plan de mejoras

Documento consolidado: mejoras identificadas en reviews del motor (impacto, riesgo, tipo). No es wishlist; es orden de trabajo para evolución del fork.

---

## Contrato actual y dependencias

### renderFill / renderStroke
- Una llamada a `nvgFill()` → un único `renderFill` con **todos** los paths y **un** bounds global.
- Una llamada a `nvgStroke()` → un único `renderStroke` con todos los paths.
- Para culling por path hace falta: **bounds por path** y filtrar la lista de paths antes de llamar al backend (o implementar culling dentro del backend por path).

### Bounds
- `cache->bounds` es un AABB global; además está implementado `path->bounds[4]` por path.
- Bounds por path se usan para: culling por path, cache por path, stats y debug visual.

### styleDirty
- Se marca pero **no corta** ningún flujo; siempre se ejecuta expandFill/expandStroke.
- Para que el cache (niveles 1 y 2) sirva, hace falta usar styleDirty para reusar geometría expandida.

---

## Mejoras 1–10 (primera review)

| # | Mejora | Resumen | Impacto | Riesgo |
|---|--------|---------|---------|--------|
| 1 | Snap stroke inner/outer | Snap solo en el borde activo; compensar desplazamiento (inner=snap hacia dentro, outer=hacia fuera). | Alto visual | Bajo |
| 2 | Pixel snap selectivo por path | NVG_PATH_PIXEL_SNAP; marcar en nvgRect, nvgRoundedRect, nvgLineTo (axis-aligned). No snap en curvas ni paths rotados. | Alto | Medio |
| 3 | Culling por bounds + scissor | Antes de renderFill/renderStroke: `if (!intersect(bounds, scissor)) skip`. Requiere bounds por path y filtrar lista de paths. | Alto | Medio |
| 4 | Cache geometría persistente | geomHash + styleHash; si coinciden → reusar verts. UI estática ≈ 0 CPU. | Muy alto | Medio |
| 5 | Tessellation / curve subdivision | clamp(n, 2, maxCurveSegments); límite en recursión Bézier también. | Seguridad/calidad | Bajo |
| 6 | Triángulos degenerados | Post-expand: `if (area(tri) < 1e-6f) skip`. | Medio | Bajo |
| 7 | AA según escala | Desactivar AA si scale < 0.75 o scale > 3.0. | Medio-alto | Bajo |
| 8 | Miter máximo en píxeles | maxMiterPx = 4.0f * devicePxRatio; si miterLen > maxMiterPx → bevel. | Alto UI | Bajo |
| 9 | Caps según orientación | En líneas H/V: caps más planos, menos subdivisiones. | Medio | Medio |
| 10 | Instrumentación debug | ctx->stats: paths, verts, culled, reused; nvgGetStats(ctx, out). | Muy alto (dev) | Cero |

---

## Mejoras 11–18 (segunda review) - Orden de implementación

**Criterios de priorización:**
1. **Seguridad primero**: Protección contra OOM y freezes
2. **Base sólida**: Mejoras de cache y estado que potencian otras optimizaciones
3. **Bajo riesgo, alto valor**: Mejoras de calidad y debug
4. **Optimizaciones**: Fast paths y hints de rendimiento
5. **Ajustes backend**: Requieren coordinación con backend

### Orden sugerido de implementación:

| Prioridad | # | Mejora | Resumen | Impacto | Riesgo | Tipo | Justificación |
|-----------|---|--------|---------|---------|--------|------|---------------|
| **1** | 13 | Límite memoria por frame | nverts > MAX_VERTS_PER_FRAME → abortPath; evita freezes y OOM. | Seguridad | Cero | core | **Ya parcialmente implementado** - completar validación en todos los puntos de expansión |
| **2** | 16 | Stats por categoría | culledPaths, reusedGeom, expandedPaths, skippedExpand. | Alto (dev) | Cero | debug/core | **Extender stats existentes** - bajo riesgo, alto valor para debugging |
| **3** | 14 | Dirty por estado relevante | fillStyleDirty vs strokeStyleDirty; cambiar fill no invalida stroke, etc. | Alto | Medio | core | **Mejora cache** - potencia otras optimizaciones, reduce CPU en UI estática |
| **4** | 11 | Orden estable / coherencia temporal | path->stableId incremental; orden fijo al expandir/render; menos jitter con scroll/resize/fade. | Medio | Bajo | core | **Mejora calidad visual** - bajo riesgo, mejora experiencia de usuario |
| **5** | 12 | Winding explícito tras flatten | Calcular área por path; forzar CCW/CW según fillRule; culling y joins más fiables. | Medio | Bajo | core | **Mejora calidad** - bajo riesgo, corrige posibles problemas de winding |
| **6** | 18 | Fast path rects axis-aligned | Detectar rect/roundedRect simple; expansión directa sin flatten completo. | Alto UI | Medio | core | **Optimización importante** - alto impacto en UI con muchos rectángulos |
| **7** | 15 | Hint NVG_PATH_STATIC | nvgBeginPathEx(ctx, NVG_PATH_STATIC); cache agresivo, menos liberaciones. | Alto UI | Bajo | API + core | **Optimización con hint** - bajo riesgo, requiere cambios API |
| **8** | 17 | Backend clip correctness | NVG_BACKEND_CLIP_EXACT; ajustar inflado de bounds y culling según backend. | Medio | Bajo | core ↔ backend | **Ajuste backend** - requiere coordinación, impacto medio |

### Tabla original (referencia):

| # | Mejora | Resumen | Impacto | Riesgo | Tipo |
|---|--------|---------|---------|--------|------|
| 11 | Orden estable / coherencia temporal | path->stableId incremental; orden fijo al expandir/render; menos jitter con scroll/resize/fade. | Medio | Bajo | core |
| 12 | Winding explícito tras flatten | Calcular área por path; forzar CCW/CW según fillRule; culling y joins más fiables. | Medio | Bajo | core |
| 13 | Límite memoria por frame | nverts > MAX_VERTS_PER_FRAME → abortPath; evita freezes y OOM. | Seguridad | Cero | core |
| 14 | Dirty por estado relevante | fillStyleDirty vs strokeStyleDirty; cambiar fill no invalida stroke, etc. | Alto | Medio | core |
| 15 | Hint NVG_PATH_STATIC | nvgBeginPathEx(ctx, NVG_PATH_STATIC); cache agresivo, menos liberaciones. | Alto UI | Bajo | API + core |
| 16 | Stats por categoría | culledPaths, reusedGeom, expandedPaths, skippedExpand. | Alto (dev) | Cero | debug/core |
| 17 | Backend clip correctness | NVG_BACKEND_CLIP_EXACT; ajustar inflado de bounds y culling según backend. | Medio | Bajo | core ↔ backend |
| 18 | Fast path rects axis-aligned | Detectar rect/roundedRect simple; expansión directa sin flatten completo. | Alto UI | Medio | core |

---

## Mejoras estructurales (cache y pipeline)

### Tres niveles de cache (1 estructural)
- **Nivel 1:** Path commands (`ctx->commands`) → dirty: geomDirty.
- **Nivel 2:** Flattened points (`cache->points`, `cache->paths`) → dirty: geomDirty.
- **Nivel 3:** Expanded geometry (verts fill/stroke) → dirty: styleDirty.

Implementado: el hit de cache usa `expandHash` (parámetros que afectan al expand: useAA, scissor; en stroke además lineCap, lineJoin, width, miter). Si geomHash + expandHash coinciden, se reutilizan los verts aunque cambie solo paint/color/composite; no se re-expande.

### Fill y stroke caches separados (2 estructural)
- fillCache y strokeCache con verts, nverts, bounds por path, hash.
- Stroke no invalida fill.

### Path instanced (3, opcional)
- Path en espacio local; transform en expand o backend; reutilizar misma geometría (iconos, knobs).

---

## Otras mejoras puntuales

- **Stroke 1px auto inner:** strokeWidth ≤ 1px, sin rotación, axis-aligned → forzar NVG_STROKE_INNER (estilo D2D/Skia).
- **Vértices redundantes post-expand:** colineales y tris con área < eps → skip.
- **AA por ángulo:** ✅ **Implementado** - Reducir fringe en ángulos muy agudos, stroke fino, zoom alto.
- **Debug visual:** NVG_DEBUG_BOUNDS, NVG_DEBUG_JOINS, NVG_DEBUG_CAPS, NVG_DEBUG_CULL; dibujar bounds, joins, caps, paths culled.
- **Culling jerárquico:** ✅ **Implementado** - Con path->bounds, fill convex → cull más agresivo; bounds << scissor → skip expand.
- **Flush text texture una vez por frame:** ✅ **Implementado** - Optimización para reducir actualizaciones de textura; flush al final del frame en lugar de múltiples veces durante el frame.

---

## Orden de implementación sugerido

---

## Implementado (primera tanda)

### Mejoras 1-10: Estado actual

| # | Mejora | Estado | Notas |
|---|--------|--------|-------|
| 1 | Snap stroke inner/outer | ✅ **Activo** | Implementado con flags `NVG_STROKE_INNER`, `NVG_STROKE_OUTER`, `NVG_STROKE_PIXEL_SNAP` |
| 2 | Pixel snap selectivo por path | ✅ **Activo** | Implementado con `NVG_PATH_PIXEL_SNAP` en path flags |
| 3 | Culling por bounds + scissor | ✅ **Activo** | Implementado con margen de seguridad de 2.0px para evitar culling agresivo |
| 4 | Cache geometría persistente | ✅ **Activo** | Implementado con `geomHash` y `expandHash`; fill y stroke caches separados |
| 5 | Tessellation / curve subdivision | ✅ **Activo** | Límites: `NVG_MAX_CURVE_SEGS`, `NVG_MAX_BEZIER_DEPTH` |
| 6 | Triángulos degenerados | ❌ **Desactivado** | Causaba deformación en rectángulos y formas simples; función presente pero retorna inmediatamente |
| 7 | AA según escala | ✅ **Activo** | Desactiva AA si `scale < 0.25` o `scale > 8.0` |
| 8 | Miter máximo en píxeles | ✅ **Activo** | `maxMiterPx = 4.0f` |
| 9 | Caps según orientación | ✅ **Activo** | Optimización de caps redondos en líneas H/V |
| 10 | Instrumentación debug | ✅ **Activo** | `NVGstats` struct y `nvgGetStats()` implementados |

**Constantes definidas:**
- `NVG_MAX_VERTS_PER_FRAME` (límite de seguridad)
- `NVG_MAX_CURVE_SEGS`, `NVG_MAX_BEZIER_DEPTH` (límites de subdivisión)
- `NVG_DEGEN_TRI_AREA_EPS`, `NVG_DEGEN_TRI_MIN_VERTICES`, `NVG_DEGEN_TRI_MIN_PATH_AREA`, `NVG_DEGEN_TRI_AREA_RATIO` (filtro degenerados - no usado actualmente)

**API adicional:**
- `nvgGetStats(NVGcontext* ctx, NVGstats* stats)`
- `nvgBeginPathEx(NVGcontext* ctx, unsigned int flags)`
- `nvgSetFlagsEx(NVGcontext* ctx, unsigned int flags)`
- `nvgGetFlagsEx(NVGcontext* ctx)`

**Problemas conocidos:**
- Mejora 6 (Triángulos degenerados): Desactivada por causar deformación visual en formas geométricas simples. La función está presente pero no procesa nada.

### Mejoras 11-18: Estado actual

| # | Mejora | Estado | Notas |
|---|--------|--------|-------|
| 11 | Orden estable / coherencia temporal | ✅ **Activo** | Implementado con `stableId` en `NVGpath` y ordenamiento antes de expandir/render |
| 12 | Winding explícito tras flatten | ✅ **Activo** | Implementado con cálculo de área por path y corrección explícita de winding |
| 13 | Límite memoria por frame | ✅ **Activo** | Implementado con `NVG_MAX_VERTS_PER_FRAME` en todos los puntos de expansión y cache |
| 14 | Dirty por estado relevante | ✅ **Activo** | Implementado con `fillStyleDirty` y `strokeStyleDirty` separados para cache granular |
| 15 | Hint NVG_PATH_STATIC | ✅ **Activo** | Implementado con preservación de paths estáticos en cache; `nvgBeginPathEx(ctx, NVG_PATH_STATIC)` marca paths para cache agresivo |
| 16 | Stats por categoría | ✅ **Activo** | `NVGstats` con contadores `expandedPaths`, `culledPaths`, `reusedGeom`, `skippedExpand` |
| 17 | Backend clip correctness | ✅ **Activo** | Implementado con `backendClipExact` en `NVGparams`; margen de culling ajustado según backend (0.5px para exacto, 2.0px para conservador) |
| 18 | Fast path rects axis-aligned | ✅ **Activo** | Implementado con detección de rectángulos simples y expansión directa optimizada |

### Mejoras adicionales (optimizaciones identificadas)

| # | Mejora | Estado | Notas |
|---|--------|--------|-------|
| 1 | Stroke 1px auto inner | ✅ **Activo** | Implementado automáticamente: cuando `strokeWidth ≤ 1px`, sin rotación y paths axis-aligned, se aplica `NVG_STROKE_INNER` automáticamente. No requiere configuración explícita. |
| 3 | AA por ángulo | ✅ **Activo** | Implementado con reducción automática de fringe en ángulos agudos (< 30°) y muy obtusos (> 150°). Solo se activa cuando `strokeWidth ≤ 2px` y `scale ≥ 1.0`. Mejora calidad visual sin configuración adicional. |
| 5 | Culling jerárquico | ✅ **Activo** | Implementado con culling más agresivo para paths convexos (margen 50% menor) y skip expand cuando bounds << scissor (área path < 5% del área scissor Y path < 100px²). Mejora rendimiento en scroll views y listas grandes. |
| 6 | Flush text texture una vez por frame | ✅ **Activo** | Implementado con flag `textTextureDirty`; `nvgText` marca el flag, flush se hace una vez en `nvgEndFrame`. `nvg__allocTextAtlas` sigue haciendo flush inmediato cuando cambia de atlas. |

---

*Fork: https://github.com/fedealvez/nanovg. Pipeline sRGB end-to-end; linear no activo salvo backend linear-aware.*




/////////////////////////////
english:
# NanoVG fork – Engine review and improvement plan

Consolidated document: improvements identified in engine reviews (impact, risk, type). This is not a wishlist; it's a work order for the fork's evolution.

---

## Current contract and dependencies

### renderFill / renderStroke
- One call to `nvgFill()` → a single `renderFill` with **all** paths and **one** global bounds.

- One call to `nvgStroke()` → a single `renderStroke` with all paths.

- For path culling, you need: **path-bounds** and to filter the list of paths before calling the backend (or implement path culling within the backend).

### Bounds
- `cache->bounds` is a global bounds block; `path->bounds[4]` is also implemented for each path.

- Bounds by path are used for: path culling, path caching, stats, and visual debugging.

### styleDirty
- It is checked but **does not** interrupt any flow; expandFill/expandStroke is always executed.

- For caching (levels 1 and 2) to work, styleDirty must be used to reuse expanded geometry.

---

## Improvements 1–10 (first review)

| # | Improvement | Summary | Impact | Risk |

---|--------|---------|---------|--------|

1 | Snap stroke inner/outer | Snap only on the active edge; compensate for displacement (inner = snap inward, outer = snap outward). | High visual impact | Low visual impact |

2 | Selective pixel snap by path | NVG_PATH_PIXEL_SNAP; check nvgRect, nvgRoundedRect, nvgLineTo (axis-aligned). No snapping on curves or rotated paths. | High | Medium |

| 3 | Culling by bounds + scissor | Before renderFill/renderStroke: `if (!intersect(bounds, scissor)) skip`. Requires bounds by path and filtering the path list. | High | Medium |

| 4 | Persistent geometry cache | geomHash + styleHash; if they match → reuse verts. Static UI ≈ 0 CPU. | Very High | Medium |

| 5 | Tessellation / curve subdivision | clamp(n, 2, maxCurveSegments); also limits Bézier recursion. | Safety/quality | Low |

| 6 | Degenerate triangles | Post-expand: `if (area(tri) < 1e-6f) skip`. | Medium | Low |

| 7 | Scale-based AA | Disable AA if scale < 0.75 or scale > 3.0. | Medium-high | Low |

| 8 | Maximum miter in pixels | maxMiterPx = 4.0f * devicePxRatio; if miterLen > maxMiterPx → bevel. | High UI | Low |

| 9 | Caps based on orientation | On H/V lines: flatter caps, fewer subdivisions. | Medium | Medium |

| 10 | Debug instrumentation | ctx->stats: paths, verts, culled, reused; nvgGetStats(ctx, out). | Very high (dev) | Zero |

---

## Improvements 11–18 (Second Review) - Implementation Order

**Prioritization Criteria:**
1. **Security First**: Protection against OOM and freezes
2. **Solid Foundation**: Cache and state improvements that enhance other optimizations
3. **Low Risk, High Value**: Quality and debug improvements
4. **Optimizations**: Fast paths and performance hints
5. **Backend Tuning**: Require backend coordination

### Suggested Implementation Order:

| Priority | # | Improvement | Summary | Impact | Risk | Type | Justification |

|-----------|---|--------|---------|---------|--------|------|---------------|

**1** | 13 | Memory Limit per Frame | nverts > MAX_VERTS_PER_FRAME → abortPath; prevents freezes and OOM. | Security | Zero | core | **Partially Implemented** - Complete validation at all expansion points |

**2** | 16 | Stats by Category | culledPaths, reusedGeom, expandedPaths, skippedExpand. | High (dev) | Zero | debug/core | **Extend existing stats** - Low risk, high value for debugging |

**3** | 14 | Dirty by relevant state | fillStyleDirty vs strokeStyleDirty; changing fill doesn't invalidate stroke, etc. | High | Medium | core | **Improve cache** - Powers other optimizations, reduces CPU usage in static UI |

**4** | 11 | Stable ordering / temporal consistency | incremental path->stableId; fixed order when expanding/rendering; less jitter with scrolling/resize/fade. | Medium | Low | core | **Improve visual quality** - Low risk, improves user experience |

**5** | 12 | Explicit winding after flattening | Calculate area by path; force CCW/CW based on fillRule; more reliable culling and joins. | Medium | Low | Core | **Quality Improvement** - low risk, fixes potential winding issues |

| **6** | 18 | Fast path axis-aligned rects | Detect simple rect/rounded Rects; direct expansion without full flattening. | High UI | Medium | Core | **Important Optimization** - high UI impact with many rectangles |

| **7** | 15 | Hint NVG_PATH_STATIC | nvgBeginPathEx(ctx, NVG_PATH_STATIC); aggressive caching, fewer releases. | High UI | Low | API + Core | **Optimization with hint** - low risk, requires API changes |

| **8** | 17 | Backend clip correctness | NVG_BACKEND_CLIP_EXACT; adjust bound inflation and culling based on backend. | Medium | Low | Core ↔ Backend | **Backend Tuning** - requires coordination, medium impact |

### Original Table (reference):

| # | Improvement | Summary | Impact | Risk | Type |

|---|--------|---------|---------|--------|------|

11 | Stable order / temporal consistency | path->st