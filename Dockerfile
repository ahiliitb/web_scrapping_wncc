FROM python:3.9
COPY . /soc
WORKDIR /soc
RUN pip install requests
RUN pip install pandas
RUN pip install bs4

CMD ["python", "webscraping.py"]