import requests # 导入requests库
import re # 导入正则表达式
import time

def loadPage(url):
    '''
    访问目标地址，并返回网页源代码

    '''
    response = requests.get(url=url).content # 访问目标网址
    response = str(response, 'utf-8')
    return response

def match(rule, html):
    '''
    利用正则表达式从源代码中匹配想要获取的内容
    '''
    result = re.findall(rule,html)
    return result
def dataSave(datas):
    '''
    将获得的数据写入txt文档
    '''
    for data in datas:
        with open("豆瓣Top250.txt", 'a', encoding='utf-8') as f:
            f.write(data)
def main():
    '''
        250个电影，一页显示25个，总共10页，即url地址start=后累加9次
    '''
    # 添加浏览器用户代理
    # hearders = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) "
    #                   "Chrome/58.0.3029.110 Safari/537.36 SE 2.X MetaSr 1.0"
    # }
    url = "https://movie.douban.com/top250?start=" # 豆瓣top250网址,strart=后面加页数，比如第一页就是0，第二页是25，每次累加25
    rules = r'<div class="hd">([\d\D]*)</li>' # 正则表达式匹配电影信息
    for i in range(10):
        whole_url = url + str(i*25)
        print("正在获取第%d页" %(i+1))
        content = loadPage(whole_url) # 获取每一页的内容
        datas = match(rules, content)  # 获取电影内容
        dataSave(datas)  # 将数据写入文件
        time.sleep(3) # 每获取一页等3s后再获取下一页
if __name__ == '__main__':
    main()
