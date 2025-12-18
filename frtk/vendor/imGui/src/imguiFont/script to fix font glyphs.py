import fontforge
import psMat

def fixVerticalSize:
    font = fontforge.activeFont()

    EM = font.em
    ASCENT = font.ascent
    DESCENT = font.descent

    for g in font.glyphs():
        if not g.isWorthOutputting():
            continue

        xmin, ymin, xmax, ymax = g.boundingBox()
        glyph_center = (ymin + ymax) / 2

        # Target center of em (icon-font style)
        target_center = (ASCENT - DESCENT) / 2

        dy = target_center - glyph_center

        g.transform(psMat.translate(0, dy))
        g.round()

    print("Vertical centering complete.")

def fixAllSVgIcons:

    font = fontforge.activeFont()

    for g in font.glyphs():
        if not g.isWorthOutputting():
            continue

        # Fix contour direction
        g.correctDirection()

        # Remove overlaps
        g.removeOverlap()

        # Add missing extrema
        g.addExtrema()

        # Simplify tiny errors
        g.simplify()

        # Round coordinates to integers
        g.round()

        # Auto-hinting (optional for icons)
        g.autoHint()

    print("Auto-fix completed for all glyphs.")


import fontforge
import psMat
def fixDiffSizeOfDiffSvg:


    font = fontforge.activeFont()

    # Collect bounding boxes of all glyphs
    max_width = 0
    max_height = 0

    glyphs = [g for g in font.glyphs() if g.isWorthOutputting()]

    for g in glyphs:
        xmin, ymin, xmax, ymax = g.boundingBox()
        width = xmax - xmin
        height = ymax - ymin

        max_width = max(max_width, width)
        max_height = max(max_height, height)

    print("Max width:", max_width)
    print("Max height:", max_height)

    # Scale all glyphs to match the largest glyph
    for g in glyphs:
        xmin, ymin, xmax, ymax = g.boundingBox()
        width = xmax - xmin
        height = ymax - ymin

        if width == 0 or height == 0:
            continue

        scale_x = max_width / width
        scale_y = max_height / height
        scale = min(scale_x, scale_y)  # preserve aspect ratio

        # Move glyph to origin
        g.transform(psMat.translate(-xmin, -ymin))

        # Scale glyph
        g.transform(psMat.scale(scale))

        # Re-center glyph
        new_xmin, new_ymin, new_xmax, new_ymax = g.boundingBox()
        dx = (max_width - (new_xmax - new_xmin)) / 2
        dy = (max_height - (new_ymax - new_ymin)) / 2
        g.transform(psMat.translate(dx, dy))

        g.round()

    print("All glyphs scaled and standardized.")
