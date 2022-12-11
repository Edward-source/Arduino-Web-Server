import requests as r
import json

server_url = "http://192.168.1.50:80"

class Client():

    def Get(self, url:str):
        result = r.get(url)
        print(result.status_code)
        print(result.content)

    def Post(self, url: str, data :dict):

        payload = {'user': data}
        result = r.post(url, json = payload)

        print(result.status_code)
        if result.status_code == 200:
             print("200 OK")
        print(result.content)




client = Client()

client.Post(server_url, {"id": 1,
                        "first_name": "Edward",
                        "Last_Name" : "Tladi"})