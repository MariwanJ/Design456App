"""
This Python script converts a TTF font file into:
  1. A C header file (glyphs.h) containing #define macros for each glyph.
  2. An HTML file (glyphs.html) visualizing the glyphs and codepoints.
"""

from fontTools.ttLib import TTFont
import os


def load_unicode_mapping(font):
    """Extract a mapping of glyph_name -> unicode_code from the font."""
    mapping = {}

    for cmap in font["cmap"].tables:
        if cmap.platformID == 3 and cmap.platEncID == 1:  # Unicode BMP
            for code, glyph_name in cmap.cmap.items():
                mapping[glyph_name] = code

    return mapping


def write_header_file(mapping, filename="glyphs.h"):
    """Generate a C header file defining glyph macros."""
    with open(filename, "w") as f:
        f.write("#ifndef GLYPHS_H\n#define GLYPHS_H\n\n")

        for glyph_name, code in mapping.items():
            macro = f"GLYPH_{glyph_name.upper()}"
            macro = macro.replace('-', '_')

            # Convert code point to character
            character = chr(code)

            # Encode character as UTF-8 and create a bytes representation
            utf8_bytes = character.encode('utf-8')

            # Format bytes as a string representation
            byte_string = ''.join(f"\\x{byte:02x}" for byte in utf8_bytes)

            f.write(f"#define {macro}           \"{byte_string}\"\n")

        f.write("\n#define ICON_MIN  	0x21")
        f.write("\n#define ICON_MAX    0xF8FF")
        f.write("\n#endif // GLYPHS_H\n")


def write_html_file(mapping, font_path, filename="glyphs.html"):
    """Generate an HTML file displaying glyphs in a table."""
    html = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Font Glyphs</title>
    <style>
        @font-face {{
            font-family: 'CustomFont';
            src: url('{font_path}') format('truetype');
        }}
        body {{ font-family: Arial, sans-serif; }}
        table {{ width: 60%; border-collapse: collapse; }}
        th, td {{ border: 1px solid #ddd; padding: 8px; text-align: left; }}
        th {{ background-color: #f2f2f2; }}
        .glyph {{ font-family: 'CustomFont'; font-size: 48px; }}
    </style>
</head>
<body>
    <h1>Font Glyphs</h1>
    <table>
        <tr>
            <th>Unicode Code Point</th>
            <th>Glyph</th>
            <th>Header Macro</th>
            <th>CODE</th>
        </tr>
"""

    for glyph_name, code in mapping.items():
        macro = f"GLYPH_{glyph_name.upper()}"
        macro=macro.replace('-','_')
        macro=macro.replace('_','_')
        html += f"""
        <tr>
            <td>U+{code:X}</td>
            <td class="glyph">&#x{code:X};</td>
            <td>#define {macro}</td>
            <td> 0x{code:X}</td>

        </tr>
"""

    html += """
    </table>
</body>
</html>
"""

    with open(filename, "w") as f:
        f.write(html)


def main():
    
    font_path = input("Enter font path & name: ")

    if not os.path.isfile(font_path) or not font_path.lower().endswith(".ttf"):
        print("Invalid file. Please provide a valid .ttf font file path.")
        return

    font = TTFont(font_path)

    unicode_mapping = load_unicode_mapping(font)
    write_header_file(unicode_mapping)
    write_html_file(unicode_mapping, font_path)

    print("Files generated: glyphs.h and glyphs.html")


if __name__ == "__main__":
    main()
