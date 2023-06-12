# 
#
#
# Stephen Oakley
# 24 November 2019
#
# This python script is meant to convert text to an image. 
# This image will then be used by the project ColorImage to display.
# This script also requires 
#
#

import sys
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

# - Define the font size and type
fontType = "Arial.ttf"
fontSize = 9
# place holder to be filled in with sys.argv's
text = ""
textColor = "white"
textBackground = "grey"
savePath = sys.argv[1]

for i in sys.argv[2:]:
    text += i + " "


font = ImageFont.truetype(fontType, fontSize)
#width, height = getSize(text, font)





img = Image.new('RGB', (270, 25), textBackground)
d = ImageDraw.Draw(img)

d.text((5, 5), text, fill=textColor)

text_width, text_height = d.textsize('Hello')

#img = Image.new('RGB', (200, 100), (255, 255, 255))



#s = cStringIO.StringIO()
img.save(savePath+'/'+'tester.ppm', 'ppm')
img.save
#img.show()

#in_memory_file = s.getvalue()
