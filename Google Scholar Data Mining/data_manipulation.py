import os
import csv
import requests
from bs4 import BeautifulSoup
import webbrowser
import jellyfish
from nltk.corpus import wordnet

from difflib import SequenceMatcher

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

with open('input_KS_data.csv', "r", encoding="utf-8") as csvfile:
    read = csv.reader(csvfile)
    head = []
    lines = []

    s = SequenceMatcher(0)

    for r in read:
        for w in r:
            head.append(r)
            break
        break

    for r in read:
        lines.append(r)

    csv_lines = []
    p = 0
    for l in lines:
        if l[8] is "":
            test_data = score_keyphrases_by_textrank(l[3], 0.9)
            keywords = ""
            for t in test_data[:10]:
                keywords += t[0] + ", "

            l[8] = keywords
    ratios = []
    matched_name = ""
    for l in lines:
        c_ratio = 0.0
        max_ratio = 999
        key_name = ""

        co_ratio = 0
        c_max_ratio = 999
        u_name = ""
        co_name = ""

        s.set_seq1(str(l[0]).lower())
        for au in l[5].split(","):
            s.set_seq2(str(au).lower())
            ratios.append(s.ratio())
            c_ratio = jellyfish.levenshtein_distance(str(l[0]).lower().strip(), str(au).strip())
            if max_ratio > c_ratio:
                max_ratio = c_ratio
                key_name = au

        for co in l[2].split(","):
            s.set_seq1(str(co).lower())
            for au in l[5].split(","):
                s.set_seq2(str(au).lower())
                ratios.append(s.ratio())
                co_ratio = jellyfish.levenshtein_distance(str(co).lower().strip(), str(au).strip())
                if c_max_ratio > co_ratio:
                    c_max_ratio = co_ratio
                    u_name = au
                    co_name = co

        print(max_ratio, "\t", l[0], "\t", key_name, "\t", c_max_ratio, "\t", co_name, "\t\t\t", u_name, "\n")
        p += 1
        csv_lines.append([str(p), l[4], str(max_ratio), str(c_max_ratio)])

myfile = open('num_data.csv', 'w', encoding='utf-8')
for p in csv_lines:
    for w in p:
        txt = "\"" + w+ "\","
        myfile.write(txt)
    myfile.write("\n")
myfile.close()

"""
    print("Ratio\t", head[0][2], "\t\t\t", head[0][8])
    for l in lines:
        max_ratio = 0.0
        rea_int = ""
        key_words = ""

        for s1 in l[2].split(","):
            wordFromList1 = wordnet.synsets(str(s1).lower())
            for s2 in l[8].split(","):
                s.set_seq1(str(s2).lower())
                wordFromList2 = wordnet.synsets(str(s2).lower())

                if s.ratio() >= max_ratio:
                    max_ratio = s.ratio()
                    rea_int = str(s1).lower()
                    key_words = str(s2).lower()

    print(round(max_ratio, 2), "\t", rea_int, "\t\t\t", key_words, "\n")

    for l in lines[:10]:
        max_ratio = 0.0
        rea_int = ""
        key_words = ""

        for s1 in l[2].split(","):
            s.set_seq2(str(s1).lower())
            for s2 in l[8].split(","):
                s.set_seq1(str(s2).lower())
                if s.ratio() >= max_ratio:
                    max_ratio = s.ratio()
                    rea_int = str(s1).lower()
                    key_words = str(s2).lower()

        print(round(max_ratio, 2), "\t", rea_int, "\t\t\t", key_words, "\t\t\t", l[3], ": ", l[8], "\n")

    for l in lines:
        max_ratio = 0.0
        rea_int = ""
        key_words = ""
        list = []
        flag = 1
        for s1 in l[2].split(","):
            wordFromList1 = wordnet.synsets(str(s1).lower())
            for s2 in l[8].split(","):
                s.set_seq1(str(s2).lower())
                wordFromList2 = wordnet.synsets(str(s2).lower())

                if wordFromList1 and wordFromList2:
                    s123 = wordFromList1[0].wup_similarity(wordFromList2[0])
                    list.append(s123)
                    rea_int = str(s1).lower()
                    key_words = str(s2).lower()
                else:
                    flag = 0
        if flag == 1:
            print(round(max(list), 2), "\t", rea_int, "\t\t\t", key_words, "\n")
        else:
            print(0.0, "\t", rea_int, "\t\t\t", key_words, "\n")
"""
