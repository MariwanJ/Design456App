color_definitions = """
    #define FR_TRANSPARENCY          0.0000f,  0.0000f,  0.0000f,  0.0000f         
    #define FR_BLACK                 0.0000f,  0.0000f,  0.0000f,  1.0000f
    #define FR_BROWN                 0.6471f,  0.1647f,  0.1647f,  1.0000f
    #define FR_ROSYBROWN             0.7373f,  0.5608f,  0.5608f,  1.0000f
    #define FR_CHOCOLATE             0.8235f,  0.4118f,  0.1176f,  1.0000f
    #define FR_SADDLEBROWN           0.5451f,  0.2706f,  0.0745f,  1.0000f
    #define FR_TAN                   0.8235f,  0.7059f,  0.5490f,  1.0000f   
    #define FR_ORANGERED             1.0000f,  0.2706f,  0.0000f,  1.0000f
    #define FR_WINGS3D               0.3800f,  0.3800f,  0.3800f,  0.5000f

    #define FR_PURPLE                0.5020f,  0.0000f,  0.5020f,  1.0000f
    #define FR_FUCHSIA               1.0000f,  0.0000f,  1.0000f,  1.0000f
    #define FR_VIOLET                0.9333f,  0.5098f,  0.9333f,  1.0000f
    #define FR_ORCHID                0.8549f,  0.4392f,  0.8392f,  1.0000f
    #define FR_MEDIUMPURPLE          0.5765f,  0.4392f,  0.8588f,  1.0000f
    #define FR_AMETHYST              0.6000f,  0.4000f,  0.8000f,  1.0000f
    #define FR_DARKVIOLET            0.5804f,  0.0000f,  0.8275f,  1.0000f
    #define FR_TURQUOISE             0.2510f,  0.8784f,  0.8157f,  1.0000f
    #define FR_AQUAMARINE            0.4980f,  1.0000f,  0.8314f,  1.0000f
    #define FR_DARK_SHADOW           0.0000f,  0.0000f,  0.0000f,  0.6510f
    #define FR_DARKBLUE              0.0000f,  0.0000f,  0.5451f,  1.0000f
    #define FR_CHARCOAL              0.2110f,  0.2110f,  0.2110f,  1.0000f
    #define FR_GAINSBORO             0.8627f,  0.8627f,  0.8627f,  1.0000f
    #define FR_DESIGN456_GRID        0.7410f,  0.8820f,  0.9220f,  1.0000f

    //Grays
    #define FR_GRAY                  0.5020f,  0.5020f,  0.5020f,  1.0000f
    #define FR_DARK_GRAY             0.6620f,  0.6620f,  0.6620f,  1.0000f
    #define FR_DIM_GRAY              0.4120f,  0.4120f,  0.4120f,  1.0000f
    #define FR_LIGHT_GRAY            0.8280f,  0.8280f,  0.8280f,  1.0000f
    #define FR_LIGHT_GRAY_90         0.9010f,  0.9010f,  0.9010f,  1.0000f 
    #define FR_LIGHT_GRAY_93         0.9330f,  0.9330f,  0.9330f,  1.0000f 
    #define FR_LIGHT_GRAY_94         0.9490f,  0.9490f,  0.9490f,  1.0000f 
    #define FR_LIGHT_GRAY_97         0.9720f,  0.9720f,  0.9720f,  1.0000f 
    #define FR_ASH_GRAY              0.6660f,  0.6660f,  0.6660f,  1.0000f
    #define FR_CLOUD_GRAY            0.7800f,  0.7800f,  0.8000f,  1.0000f
    #define FR_SLATE_GRAY            0.4390f,  0.5020f,  0.5610f,  1.0000f
    #define FR_SLATEGRAY             0.4392f,  0.5020f,  0.5647f,  1.0000f
    #define FR_STONE_GRAY            0.4470f,  0.4470f,  0.4470f,  1.0000f
    #define FR_GREY                  0.5020f,  0.5020f,  0.5020f,  1.0000f
    #define FR_DARKSLATEGREY         0.1843f,  0.3098f,  0.3098f,  1.0000f
    #define FR_LIGHTSLATEGRAY        0.4667f,  0.5333f,  0.6000f,  1.0000f
    #define FR_DARKGREY1             0.6627f,  0.6627f,  0.6627f,  1.0000f
    #define FR_DARKGREY2             0.5627f,  0.5627f,  0.5627f,  1.0000f
    #define FR_DODGERBLUE            0.1176f,  0.5647f,  1.0000f,  1.0000f
    #define FR_LIGHTGREY             0.8275f,  0.8275f,  0.8275f,  1.0000f
    #define FR_SLATEGREY             0.4392f,  0.5020f,  0.5647f,  1.0000f
    #define FR_DARKSLATEGRAY         0.1843f,  0.3098f,  0.3098f,  1.0000f
    #define FR_PAYNE_GRAY            0.2570f,  0.2570f,  0.3220f,  1.0000f
        //Whites

    #define FR_WHITE                 1.0000f,  1.0000f,  1.0000f,  1.0000f
    #define FR_SNOW                  1.0000f,  0.9804f,  0.9804f,  1.0000f
    #define FR_ALICEBLUE             0.9412f,  0.9725f,  1.0000f,  1.0000f
    #define FR_SEASHELL              1.0000f,  0.9608f,  0.9333f,  1.0000f
    #define FR_FLORALWHITE           1.0000f,  0.9804f,  0.9412f,  1.0000f
    #define FR_IVORY                 1.0000f,  1.0000f,  0.9412f,  1.0000f
    #define FR_NAVAJOWHITE           1.0000f,  0.8706f,  0.6784f,  1.0000f
    #define FR_CORN_FLOWER_BLUE      0.3922f,  0.5843f,  0.9294f,  1.0000f
    #define FR_BLANCHEDALMOND        1.0000f,  0.9216f,  0.8039f,  1.0000f
    #define FR_LAVENDERBLUSH         1.0000f,  0.9412f,  0.9608f,  1.0000f
    #define FR_PAPAYAWHIP            1.0000f,  0.9373f,  0.8353f,  1.0000f
    #define FR_MISTYROSE             1.0000f,  0.8941f,  0.8824f,  1.0000f
    #define FR_LINEN                 0.9804f,  0.9412f,  0.9020f,  1.0000f
    #define FR_ANTIQUEWHITE          0.9804f,  0.9216f,  0.8431f,  1.0000f
    #define FR_BEIGE                 0.9608f,  0.9608f,  0.8627f,  1.0000f

        //Reds
    #define FR_RED                   1.0000f,  0.0000f,  0.0000f,  1.0000f
    #define FR_CORAL                 1.0000f,  0.4980f,  0.3137f,  1.0000f
    #define FR_CRIMSON               0.8627f,  0.0784f,  0.2353f,  1.0000f
    #define FR_DEEPPINK              1.0000f,  0.0784f,  0.5765f,  1.0000f
    #define FR_HOTPINK               1.0000f,  0.4118f,  0.7059f,  1.0000f
    #define FR_LIGHTPINK             1.0000f,  0.7137f,  0.7569f,  1.0000f
    #define FR_MEDIUMVIOLETRED       0.7804f,  0.0824f,  0.5216f,  1.0000f
    #define FR_ORANGERED             1.0000f,  0.2706f,  0.0000f,  1.0000f
    #define FR_TOMATO                1.0000f,  0.3882f,  0.2784f,  1.0000f
    #define FR_SALMON                0.9804f,  0.5020f,  0.4471f,  1.0000f
    #define FR_INDIGO                0.2941f,  0.0000f,  0.5098f,  1.0000f
    #define FR_MEDIUMORCHID          0.7294f,  0.3333f,  0.8275f,  1.0000f
        //Blues 
    #define FR_BLUE                  0.0000f,  0.0000f,  1.0000f,  1.0000f
    #define FR_NAVY                  0.0000f,  0.0000f,  0.5020f,  1.0000f
    #define FR_DEEPSKYBLUE           0.0000f,  0.7490f,  1.0000f,  1.0000f
    #define FR_CYAN                  0.0000f,  1.0000f,  1.0000f,  1.0000f
    #define FR_LIGHTSKYBLUE          0.5294f,  0.8078f,  0.9804f,  1.0000f
    #define FR_SKYBLUE               0.5294f,  0.8078f,  0.9216f,  1.0000f
    #define FR_LIGHTBLUE             0.6784f,  0.8471f,  0.9020f,  1.0000f
    #define FR_MEDIUMBLUE            0.0000f,  0.0000f,  0.8039f,  1.0000f
    #define FR_STEELBLUE             0.2745f,  0.5098f,  0.7059f,  1.0000f
    #define FR_DEEPBLUE              0.1125f,  0.1176f,  0.8196f,  1.0000f
    #define FR_ROYALBLUE             0.2549f,  0.4118f,  0.8824f,  1.0000f
    #define FR_LIGHTSTEELBLUE        0.6902f,  0.7686f,  0.8706f,  1.0000f
    #define FR_DARKCYAN              0.0000f,  0.5451f,  0.5451f,  1.0000f
    #define FR_ORANGE                1.0000f,  0.6471f,  0.0000f,  1.0000f

        //Greens 
    #define FR_GREEN                 0.0000f,  0.5020f,  0.0000f,  1.0000f
    #define FR_LIME                  0.0000f,  1.0000f,  0.0000f,  1.0000f
    #define FR_LAWNGREEN             0.4863f,  0.9882f,  0.0000f,  1.0000f
    #define FR_SEAGREEN              0.1804f,  0.5451f,  0.3412f,  1.0000f
    #define FR_MEDIUMSEAGREEN        0.2353f,  0.7020f,  0.4431f,  1.0000f
    #define FR_DARKGREEN             0.0000f,  0.3922f,  0.0000f,  1.0000f
    #define FR_GREENYELLOW           0.6784f,  1.0000f,  0.1843f,  1.0000f
    #define FR_CHARTREUSE            0.4980f,  1.0000f,  0.0000f,  1.0000f
        //Yellow 
    #define FR_YELLOW                1.0000f,  1.0000f,  0.0000f,  1.0000f
    #define FR_GOLD                  1.0000f,  0.7660f,  0.33600f, 1.0000f
    #define FR_GOLD1                 1.0000f,  0.8431f,  0.0000f,  1.0000f
    #define FR_LEMONCHIFFON          1.0000f,  0.9804f,  0.8039f,  1.0000f
    #define FR_PALEGOLDENROD         0.9333f,  0.9098f,  0.6667f,  1.0000f
    #define FR_LIGHTGOLDENRODYELLOW  0.9804f,  0.9804f,  0.8235f,  1.0000f
    #define FR_GOLDENROD             0.8549f,  0.6471f,  0.1255f,  1.0000f
    #define FR_DARKGOLDENROD         0.7216f,  0.5255f,  0.0431f,  1.0000f
    #define FR_LIGHTYELLOW           1.0000f,  1.0000f,  0.8784f,  1.0000f   

        //Metal
    #define FR_IRON                  0.5600f,  0.5700f,  0.58000f, 1.0000f
    #define FR_SILVER                0.9720f,  0.9600f,  0.91500f, 1.0000f
    #define FR_SILVER1               0.7529f,  0.7529f,  0.7529f,  1.0000f
    #define FR_ALUMINUM              0.9130f,  0.9210f,  0.92500f, 1.0000f
    #define FR_GOLD                  1.0000f,  0.7660f,  0.33600f, 1.0000f
    #define FR_GOLD1                 1.0000f,  0.8431f,  0.0000f,  1.0000f
    #define FR_COPPER                0.9550f,  0.6370f,  0.53800f, 1.0000f
    #define FR_CHROMIUM              0.5500f,  0.5560f,  0.55400f, 1.0000f
    #define FR_NICKEL                0.6600f,  0.6090f,  0.52600f, 1.0000f
    #define FR_TITANIUM              0.5420f,  0.4970f,  0.44900f, 1.0000f
    #define FR_COBALT                0.6620f,  0.6550f,  0.63400f, 1.0000f

"""
import re
# Regex to capture name and RGBA floats
pattern = re.compile(r"#define\s+(\w+)\s+([\d.]+)f,\s+([\d.]+)f,\s+([\d.]+)f,\s+([\d.]+)f")

# Convert to hex colors
colors = []
for match in pattern.finditer(color_definitions):
    name = match.group(1)
    r = float(match.group(2))
    g = float(match.group(3))
    b = float(match.group(4))
    hex_color = '#{:02X}{:02X}{:02X}'.format(int(r*255), int(g*255), int(b*255))
    colors.append((name, hex_color))

# Generate HTML
html = '<!DOCTYPE html>\n<html><head><style>'
html += """
body {font-family: sans-serif;}
.palette {
    display: flex;
    flex-wrap: wrap;
    width: 1600px; /* 10 blocks * 100px + margins */
}
.color-container {
    margin: 5px;
    text-align: center;
    width: 150px; /* each block width */
}
.color-box {
    width: 150px;
    height: 50px;
    border: 1px solid #000;
}
.color-name {
    font-size: 12px;
    margin-top: 4px;
}
"""
html += "</style></head><body>\n"
html += '<div class="palette">\n'

for name, hex_color in colors:
    html += f'<div class="color-container">'
    html += f'<div class="color-box" style="background-color:{hex_color};"></div>'
    html += f'<div class="color-name">{name}<br>{hex_color}</div>'
    html += '</div>\n'

html += '</div>\n</body></html>'

with open("colors.html", "w") as f:
    f.write(html)

print("Done!")