import fontforge
import os

# Set up paths
src_dir = "/home/dominik/Pictures/logos/svg"      # Change this to your SVG folder
output_font = "voicemailbox.ttf"  # Output font file path

font = fontforge.font()
font.encoding = "UnicodeFull"

# Set font names
font.familyname = "Voicemailbox"
font.fontname = "Voicemailbox"
font.fullname = "Voicemailbox"
font.appendSFNTName('English (US)', 'Preferred Family', 'Voicemailbox')
font.appendSFNTName('English (US)', 'Preferred Styles', 'Regular')

fontstartpointer = 65
for filename in os.listdir(src_dir):
    if filename.endswith(".svg") and filename.startswith("uni"):
        glyph = font.createChar(fontstartpointer)
        fontstartpointer += 1
        glyph.importOutlines(os.path.join(src_dir, filename))
        glyph.left_side_bearing = 50
        glyph.right_side_bearing = 50

font.generate(output_font)
