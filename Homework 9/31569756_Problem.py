import os
from bs4 import BeautifulSoup
from pymongo import MongoClient

mongoClient = MongoClient("mongodb://localhost:27017/")
stockDb      = mongoClient["stocks_db"]
stockColl    = stockDb["most_active"]

stockColl.delete_many({})

htmlFile = "most_active.html"

if not os.path.exists(htmlFile):
    print(f"Error: {htmlFile} not found.")
    exit(1)

with open(htmlFile, "r", encoding="utf-8") as fileHandle:
    pageSoup = BeautifulSoup(fileHandle, "html.parser")

stockTable = pageSoup.find("table")
if not stockTable:
    print("Stock data table not found.")
    exit(1)

dataRows = stockTable.find_all("tr")[1:]

for recordIndex, rowElem in enumerate(dataRows, start=1):
    cells = rowElem.find_all("td")
    if len(cells) < 6:
        continue

    stockRecord = {
        "Index":  recordIndex,
        "Symbol": cells[0].text.strip(),
        "Name":   cells[1].text.strip(),
        "Price":  cells[3].text.strip(),
        "Change": cells[5].text.strip(),
        "Volume": cells[6].text.strip()
    }

    stockColl.insert_one(stockRecord)

print("Stock data successfully inserted into MongoDB.")

