
import os
import csv
import requests
from bs4 import BeautifulSoup
import webbrowser





temp = os.system('Parser.py --author "Kewei sha" --csv > out.csv ')

SCHOLAR_SITE = "https://scholar.google.com/"
Author_url = ""
all_paper_info = []


with open('out.csv') as csvfile:
    read = csv.reader(csvfile)

    for row in read:
        for item in row:
            temp_URL = item
            break
        break

    #print(temp_URL)
temp_URL = "https://scholar.google.com/citations?user=wUNpA_sAAAAJ&hl=en&oi=ao"

s = requests.session()
s.cookies.clear()
req = s.get(temp_URL)

sp = BeautifulSoup(req.content)
print("**********************************")
#print(sp.prettify())

table = sp.find("div", attrs={"class":"gs_r"})

# get table of searched author
# pick the first one from the result
#print(table)


for row in table.find_all("a")[1:]:
    #print(row)
    temp = str(row.get("href"))
    #print(temp)
    Author_url = SCHOLAR_SITE + temp

print(Author_url)


def get_profile_info(author_url):
    paper = ""
    s = requests.session()
    s.cookies.clear()

    r = s.get(author_url)

    soup = BeautifulSoup(r.content)
    #print(soup.prettify())

    if soup.find("table", attrs={"id": "gsc_a_t"}) is None:
        webbrowser.open(author_url)

        s = requests.session()
        s.cookies.clear()

        r = s.get(author_url)

        soup = BeautifulSoup(r.content)
        print(soup.prettify())





    table = soup.find("table", attrs={"id": "gsc_a_t"})

    cite = []
    citation_links = []

    for row in table.find_all("tr")[1:]:

        link = row.find_all("a")
        for l in link:
            temp = str(l.get("href"))
            if temp.startswith('/citations?'):
                cite.append(temp)

    for c in cite:
        citation_links.append("https://scholar.google.com/" + c)

    #print(citation_links)

    for c in citation_links:
        req1 = requests.get(c)
        sp1 = BeautifulSoup(req1.content)
        paper_title = sp1.find("a", attrs={"class": "gsc_title_link"})
        if paper_title is not None:
            #print(paper_title.text)
            paper = paper_title.text
        for enc1 in sp1("div", attrs={"class": "gsc_value"}):
            #print(enc1.text)
            paper = paper + "|" + enc1.text
        #print(paper)


        for hreftag in sp1("a", attrs={"class": "gsc_title_link"}):
            #print(hreftag.get("href"))
            paper = paper + "|" + hreftag.get("href")
            """req2 = requests.get(hreftag.get("href") + "/keywords")
            sp2 = BeautifulSoup(req2.content)
            print(sp2)"""
        all_paper_info.append(paper)

        #print("\n==================================")

    return


get_profile_info(Author_url)
print("<<<<<<<<<<<<<<<<<=================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")


all_paper_info = list(filter(None, all_paper_info))

print(all_paper_info)


"""
myfile = open('this.csv', 'wb')
wr = csv.writer(myfile, quoting=csv.QUOTE_ALL)
wr.writerow(all_paper_info)
"""

"""
with open('nowthis.csv', 'w', newline='') as fp:
    a = csv.writer(fp, delimiter=',')
    a.writerows(all_paper_info)
"""