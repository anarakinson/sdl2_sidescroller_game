from PIL import Image
 
def convertImage(input_path):
    img = Image.open(input_path)
    img = img.convert("RGBA")
 
    datas = img.getdata()
 
    newData = []
 
    for item in datas:
        if item[0] >= 247 and item[1] >= 247 and item[2] >= 247:
            newData.append((255, 255, 255, 0))
        else:
            newData.append(item)
 
    img.putdata(newData)
    img.save("./output.png", "PNG")
    print("Successful")
 

if __name__ == "__main__":

    input_path = input("input: ")
    convertImage(input_path)

