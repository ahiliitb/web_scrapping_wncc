import requests
from bs4 import BeautifulSoup
import pandas as pd


url = "https://itc.gymkhana.iitb.ac.in/wncc/soc"

r = requests.get(url);
soup = BeautifulSoup(r.content, 'html.parser')
all_ele = soup.select('.hover-wrapper');
all_link = [];


for i in all_ele:
    temp =str(i.get('href'))
    temp = "https://itc.gymkhana.iitb.ac.in" + temp
    all_link.append(temp);


listr = [];
for i in range(71):
    url = all_link[i]
    tempr = requests.get(url)
    listr.append(tempr);


listsoup = []
for i in listr:
    tempsoup = BeautifulSoup(i.text, 'html.parser')
    listsoup.append(tempsoup);


final_lst = []
for i in range(71):
    templst = []
    templst.append(listsoup[i].find('h2', class_="display1 m-3 p-3 text-center project-title").text)
    templst.append(listsoup[i].find('h4', class_="display3").next_sibling.next_sibling.text)
    templst.append(listsoup[i].find('h4', class_="display3").next_sibling.next_sibling.next_sibling.next_sibling.next_sibling.next_sibling.text)
    final_lst.append(templst)



for i in final_lst:
    i[1] = i[1].replace("\n", "/n")
    i[2] = i[2].replace("\n", "/n")


for i in range(71):
    count = 0
    for k in range(len(final_lst[i][1])):
        if (final_lst[i][1][k] == "/"):
            count = count+1
    final_lst[i].append((count)-1);


for i in final_lst:
    i[1] = i[1].replace("/n", "/")
    i[2] = i[2].replace("/n", "")
    i[2] = i[2].replace("-", " to ")
    if(len(i[2]) == 1 or len(i[2]) == 2):
        i[2] = i[2].replace(i[2], "Upto "+i[2])


for i in final_lst:
    flag = 0
    for j in range(len(i[1])):
        if(j == 0 or j == len(i[1])-1): flag = 0;
        else: flag = 1;
        if(i[1][j] == "/" and flag == 1):
            i[1] = i[1][:j] + ',' + i[1][j+1:]
        elif(i[1][j] == "/" and flag == 0):
            i[1] = i[1][:j] + ' ' + i[1][j+1:]


for i in final_lst:
    i[1] = i[1].replace(",", ",  ")


for i in range(71):
    final_lst[i].append(all_link[i])
    final_lst[i].append("https://itc.gymkhana.iitb.ac.in"+str(listsoup[i].find('img', class_="image-1").get('src')))


dataframe = pd.DataFrame(final_lst, columns=["PROJECT TITLE", "MENTORS  ", "NO OF MENTEES", "NO OF MENTORS", "LINK FOR THE PROJECT", "PROJECT IMAGE LINK"])

print(dataframe)

dataframe.to_csv('web_scraping.csv', index=False)



