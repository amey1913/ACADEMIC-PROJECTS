from bs4 import BeautifulSoup
from pprint import pprint
f = open('acmhtml.html')

soup = BeautifulSoup(f)



def parseList(tag, level):
    for item in tag.findAll('li', recursive=False):
        for header in item.find_all('a', attrs={"class":"boxedlinkh"}):
            if header is not None:
                print(str(level) + " : " + header.text)
        for tag_a in item.find_all('a', recursive=False):
           if tag_a is not None:
                print(str(level) + " : " + tag_a.text)
        for ul in item.findAll('ul', recursive=False):
            parseList(ul, level + "     ")

        """
        if item.ul is None:
            for tag_a in item.find_all('a', recursive=False):
                if tag_a is not None:
                    print(str(level) + " : " + tag_a.text)
        elif item.name == 'ul':
            level = level + 1
            parseList(item.ul)


        for ul in item.findAll('ul', recursive=False):
            return
        for tag_a in item.find_all('a', recursive=True):
            if tag_a is not None:
                print(str(level) + " : " + tag_a.text )
                #return tag_a
                #tagg = tag_a.text
            else:
                for item in tag.findAll('ul', recursive=False):
                    level = level + 1
                    parseList(item)
"""

pprint(parseList(soup.ul, ""))

"""
    if tag.name == 'ul':

        tagg = ""
        print("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq")
        for it in tag.findAll('li'):
            print("\t"+it.text)
        print("rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr")
        return [parseList(item)
                for item in tag.findAll('li', recursive=False)]
    elif tag.name == 'li':
        if tag.ul is None:
            return tag.text
            #return "AAAAAAAAAAA"

        else:
            if tag.contents[0] is not None:
                print("---------------------------")
                print(tag.contents[0].string)
            tagg = ""
            #return (tag.contents[0].string.strip(), parseList(tag.ul))
            tag_li = tag.find("li")
            if tag_li is not None:
                tag_a = tag_li.find("a")
                if tag_a is not None:
                    print(tag_a.text)
                    tagg = tag_a.text
                #print(tag.find("li").find("a").text)
            print("================================================================================================================================")
            return (tagg, parseList(tag.ul))




"""