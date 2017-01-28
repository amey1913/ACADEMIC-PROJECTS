from nltk.sentiment.vader import SentimentIntensityAnalyzer
from nltk.corpus import stopwords
from nltk.corpus import gutenberg
import matplotlib.pyplot as plt
import nltk

# Copying data from austen-sense book into raw.
raw = gutenberg.raw('austen-sense.txt')
fw =  open("inpit.txt", "w")

# Copying book data into file.
fw.write(raw)
fw.close()

#Splitting data chapter wise.
chapters = raw.split("CHAPTER ")

pos = neg = neu = 0
out = []
line_no = 0

'''For each chapter, removig stopwords by checking each word and checking the positive,
negative or neutral flow.'''

for chapter in chapters[1:]:
    print("Chapter :", chapter[:2])

	#SentimentIntensityAnalyzer() function is used for sentiment analysis implmentation\n"
    #using NLTK to find positive/ negative meaning of the chapter.
    sid = SentimentIntensityAnalyzer()

	#If stopwords found in the chapter, then replace it with blank, so that it can not count \n'
    #for calculating positive/negative values.
    for w in chapter.split(" "):
        if w in stopwords.words('english'):
            chapter = chapter.replace(w, " ", 1)
			
    #Calculating positive, negative and neutral values using polarity_scores() function.
    ss = sid.polarity_scores(chapter)
	
    pos = ss["pos"]
    neg = ss["neg"]
    neu = ss["neu"]
    print("Positive ", pos, "Negative ", neg, "Neutral", neu)
	
    #Copying printed values in out which stores list of positive, negative and neutral values list.
    out.append([pos, neg, neu, line_no])
    line_no += 1

N = len(out)

# Considering only positive and negative values. 
p = [i[0] for i in out]
n = [i[1] for i in out]
x = [i[3] for i in out]

#Plotting flow of chapters using positive and negative values.
line, = plt.plot(x, p, lw=2, label = "Positive")
line, = plt.plot(x, n, lw=1, label = "Negative")


plt.ylabel('Frequency of Positive and Negative Polarity')
plt.xlabel('Book Chapters')
# Setting Y-axis limit.
plt.ylim(min(min(p),min(n)) - 0.1, max(max(p),max(n))  + 0.1)
plt.legend()
plt.show()
