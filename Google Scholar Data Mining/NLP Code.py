from bs4 import BeautifulSoup
from pprint import pprint
from anytree import Node, RenderTree
from anytree.dotexport import RenderTreeGraph
from anytree import PostOrderIter
import re
from difflib import SequenceMatcher

f = open('acmhtml.html')

soup = BeautifulSoup(f)
arr = [None] * 10000

parent = Node("Root", None)

# here tag is first ul
def parseList(tag, level, prev):
    current = Node(None, None)
    # go to first li level of all uls.
    for item in tag.findAll('li', recursive=False):
        # in first li level check if this level is the header li,


        for header in item.find_all('a', attrs={"class":"boxedlinkh"}):
            if header is not None:
                current = Node(header.text, parent=prev)
                #print(str(level) + " : " + header.text)


        # traverse all a's in li.
        for tag_a in item.find_all('a', recursive=False):
           if tag_a is not None:
                current = Node(tag_a.text, parent=prev)
                #print(str(level) + " : " + tag_a.text)
                # create node, parent = tag

        # traverse all uls in li
        for ul in item.findAll('ul', recursive=False):

            parseList(ul, level + "     ", current)
            # create node, parent = tag


parseList(soup.ul, "", parent)

def get_keyword_combinations(keyword):
    combination = []
    if " " in keyword:
        keyword_list = keyword.split(" ")
        key_len = len(keyword_list)

        if (key_len == 2):
            combination = keyword.split(" ")
            return combination

        if (key_len == 3):
            combination = keyword.split(" ")
            combination.append(keyword_list[0] + " " + keyword_list[1])
            combination.append(keyword_list[1] + " " + keyword_list[2])
            return combination

        if (key_len == 4):
            combination = keyword.split(" ")
            combination.append(keyword_list[0] + " " + keyword_list[1])
            combination.append(keyword_list[1] + " " + keyword_list[2])
            combination.append(keyword_list[2] + " " + keyword_list[3])
            combination.append(keyword_list[0] + " " + keyword_list[1] + " " + keyword_list[2])
            combination.append(keyword_list[1] + " " + keyword_list[2] + " " + keyword_list[3])
            return combination

def search_keywords(keyword):
    check = False
    for node in PostOrderIter(parent):
        if re.match(keyword,node.name, re.IGNORECASE):
            print("Yes, found keyword ====>> " + node.name)
            print(node.anchestors)
            check = True
    if check == False and " " in keyword:
        list_of_words = get_keyword_combinations(keyword)
        for node in PostOrderIter(parent):
            for key in list_of_words:
                #print("key = " + key + "node = " + node.name)
                if re.match(key, node.name, re.IGNORECASE):
                    print("got it.......from else  === > " + node.name)
                    print(key + "=======>>")
                    print(node.anchestors)
                    check = True

#search_keywords("image processing system")
def getKey(str1):

    for pre, fill, node in RenderTree(parent):
        s = SequenceMatcher(0)
        s.set_seq1(str1.lower())
        s.set_seq2(str(node.name).lower())
        r = s.ratio()
        if r > 0.8:
            ke = []
            for pre, fill, nod in RenderTree(node):
                ke.append(nod.name)
                for ch in node.children:
                    ke.append(ch.name)
            return ke

def extract_candidate_words(text, good_tags=set(['JJ','JJR','JJS','NN','NNP','NNS','NNPS'])):
    import itertools, nltk, string

    # exclude candidates that are stop words or entirely punctuation
    punct = set(string.punctuation)
    stop_words = set(nltk.corpus.stopwords.words('english'))
    # tokenize and POS-tag words
    tagged_words = itertools.chain.from_iterable(nltk.pos_tag_sents(nltk.word_tokenize(sent)
                                                                    for sent in nltk.sent_tokenize(text)))
    # filter on certain POS tags and lowercase all words
    candidates = [word.lower() for word, tag in tagged_words
                  if tag in good_tags and word.lower() not in stop_words
                  and not all(char in punct for char in word)]
    return candidates


def score_keyphrases_by_textrank(text, n_keywords=0.05):
    from itertools import takewhile, tee, zip_longest
    import networkx, nltk

    # tokenize for all words, and extract *candidate* words
    words = [word.lower()
             for sent in nltk.sent_tokenize(text)
             for word in nltk.word_tokenize(sent)]
    candidates = extract_candidate_words(text)
    # build graph, each node is a unique candidate
    graph = networkx.Graph()
    graph.add_nodes_from(set(candidates))

    # iterate over word-pairs, add unweighted edges into graph
    def pairwise(iterable):
        """s -> (s0,s1), (s1,s2), (s2, s3), ..."""
        a, b = tee(iterable)
        next(b, None)
        return zip_longest(a, b)

    for w1, w2 in pairwise(candidates):
        if w2:
            graph.add_edge(*sorted([w1, w2]))
    # score nodes using default pagerank algorithm, sort by score, keep top n_keywords
    ranks = networkx.pagerank(graph)
    if 0 < n_keywords < 1:
        n_keywords = int(round(len(candidates) * n_keywords))
    word_ranks = {word_rank[0]: word_rank[1]
                  for word_rank in sorted(ranks.items(), key=lambda x: x[1], reverse=True)[:n_keywords]}
    keywords = set(word_ranks.keys())
    # merge keywords into keyphrases
    keyphrases = {}
    j = 0
    for i, word in enumerate(words):
        if i < j:
            continue
        if word in keywords:
            kp_words = list(takewhile(lambda x: x in keywords, words[i:i + 10]))
            avg_pagerank = sum(word_ranks[w] for w in kp_words) / float(len(kp_words))
            keyphrases[' '.join(kp_words)] = avg_pagerank
            # counter as hackish way to ensure merged keyphrases are non-overlapping
            j = i + len(kp_words)

    return sorted(keyphrases.items(), key=lambda x: x[1], reverse=True)

text = "Abstractâ€”Image authentication verifies the originality of an image by detecting malicious manipulations. Its goal is different from that of image watermarking, which embeds into the image a signature surviving most manipulations. Most existing methods for image authentication treat all types of manipulation equally (ie, as unacceptable). However, some practical applications demand techniques that can distinguish acceptable manipulations (eg, compression) from malicious ones. In this paper, we present an effective technique for  ..."

text = "Semantic visual templates: linking visual features to semantics, Abstract The rapid growth of visual data over the last few years has lead to many schemes for retrieving such data. With content-based systems today, there exists a signijicant gap between the user's information needs and what the systems can deliver: We propose to bridge this gap, by introducing the novel idea of Semantic Visual Templates (SVT). Each template represents a personalized view of concepts (eg slalom, meetings, sunsets etc.), The SVT is represented us-ing a set of successful queries, which are generated by a two- ..."
#text = "Inverse motion compensating devices are used to transform motion compensated transform domain video signals to corresponding transform domain video signals. A compositing mechanism receives the transform domain video signals from the inverse motion compensating devices and performs transform domain video compositing operations directly on the transform domain video signals. The compositing operations result in a single composited signal incorporating each of the transform domain video signals. The single  ..."
#text = "Image authentication verifies the originality of an image by detecting malicious manipulations. Its goal is different from that of image watermarking, which embeds into the image a signature surviving most manipulations. Most existing methods for image authentication treat all types of manipulation equally (ie, as unacceptable). However, some practical applications demand techniques that can distinguish acceptable manipulations (eg, compression) from malicious ones. In this paper, we present an effective technique for  ..."
#test_data = extract_candidate_words(text)
test_data = score_keyphrases_by_textrank(text, 0.9)

k = "Multimedia, Computer Vision, Machine Learning, Signal Processing, Information Retrieval"
#k = "Internet of Things, Security and Privacy, Edge Computing, Sensor Networks"

list_of_keywords = []
for l in k.split(","):
    list_of_keywords.append(getKey(l))

list_of_keywords.remove(None)
print(list_of_keywords)

keys = []
for l in list_of_keywords:
    if type(l) is list:
        for w in l:
           keys.append(w)
    else:
        keys.append(l)

for w in keys:

    if str(w).lower() in text.lower():
        print(w)
"""
asdas = "Robustness, Authentication, Transform coding, Image coding, Watermarking, Cryptography, Discrete cosine transforms, Digital signatures, Filtering, Digital images"


#for t in test_data[0]:
for t in asdas.split(","):
    s1 = SequenceMatcher(0)
    rto = 0.0
    cr = 0.0
    p_key = ""
    a_key = ""
    for l1 in list_of_keywords:
        for l in l1:
            if l is not None and t is not None and type(l) is str and type(t) is str :
                s1.set_seq1(t)
                s1.set_seq2(l)
                cr = s1.ratio()
               # print(s1.ratio(), "\t", t, "\t", l, "\t")
                if cr > rto:
                    p_key = t
                    a_key = l
                    rto = cr
    print(rto, "\t",p_key, "\t",a_key, "\t")
"""