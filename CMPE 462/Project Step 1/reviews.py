import requests
import re
from bs4 import BeautifulSoup
import pandas as pd
from pandas import DataFrame





#-----------------------------------------------------------------------------------------------------

rates = []

reviews = []

titles = []

htmlList = []

html1 = 'https://www.imdb.com/title/tt1663202/reviews'
html2 = 'https://www.imdb.com/title/tt6294822/reviews'
html3 = 'https://www.imdb.com/title/tt8228288/reviews'
html4 = 'https://www.imdb.com/title/tt0253474/reviews'
html5 = 'https://www.imdb.com/title/tt0117500/reviews'

htmlList.append(html1)
htmlList.append(html2)
htmlList.append(html3)
htmlList.append(html4)
htmlList.append(html5)

number = 0
for html in htmlList:


    data1 = requests.get(html)

    soup = BeautifulSoup(data1.text, 'html.parser')

    content = soup.find('div', {'class': 'lister-list'})


    i = 0

    for div in content.find_all('div', {'class': 'collapsable'}):

        if i > 9:
            break

        div0 = div.find('div', {'class': 'review-container'})

        div1 = div0.find('div', {'class': 'lister-item-content'})

        div2 = div1.find('div', {'class': 'ipl-ratings-bar'})

        if str(div2).find('svg') != -1:

            span0 = div2.find('span', {'class', 'rating-other-user-rating'})
            rate = 0

            check = True
            for span in span0.find_all('span'):
                
                fake = span.text
                if check:
                    rate = int(fake)
                    check = False

            
            
            a = div1.find('a', {'class': 'title'})
            title = a.text

            div3 = div1.find('div', {'class': 'text show-more__control'})
            review = div3.text

            
            if rate >= 7:
                i = i + 1
                index = number * 10 + i

                f = open("TPR_" + str(index) + "_P.txt", "w", encoding='utf-8')
                f.write("{}\n".format(title + "\n"))
                f.write("{}\n".format(review + "\n"))
                f.close

                

    number = number + 1       

print(number)
            
        
    

       

   
    
    

    


            

    