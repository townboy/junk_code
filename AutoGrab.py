# -*- coding:utf-8 -*-  
import requests
import re
import codecs
import sys

class Grab(object):
    def __init__(self, username, userpass):
        self.username = username
        self.userpass = userpass
        self.s = requests.session()
        
    def login(self):
        url = 'http://acm.hdu.edu.cn/userloginex.php?action=login&cid=0&notice=0'
        data = { 'username' : self.username,
            'userpass' : self.userpass,
            'login' : 'Sign In'}
        try:
            Login = self.s.post(url, data)
            print Login.status_code
            
        except Exception, e:
            print e
            print 'network is not availble'
            return False

        if re.search('No such user', Login.text):
            print 'No such user or wrong password.'
            return False

        return True


    def search_rid(self):
        
        rid_pattern = re.compile('viewcode.php.rid=[0-9]*')

        def is_empty(text):
            submit = rid_pattern.findall(text)
            return True if 0 == len(submit) else False
            
        def get_text(url):
            return self.s.get(url).text

        def get_submit(text):
            date_pattern = re.compile('[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9] [0-9][0-9]:[0-9][0-9]:[0-9][0-9]')
            date = date_pattern.findall(text)
            submit = rid_pattern.findall(text)
            cpu = re.findall('<td>[0-9]*MS</td>' ,text)
            memory = re.findall('<td>[0-9]*K</td>' ,text)
            
            info = []

            for i in range(len(submit)):
                push = {
                    'date' : date[i],
                    'rid' : submit[i],
                    'cpu' : cpu[i][4:-5],
                    'memory' : memory[i][4:-5]
                    }
                info.append(push)
            return info
    

        url = 'http://acm.hdu.edu.cn/status.php?user=townboy&pid=0&lang=0&status=5&last=%s'
        now_rid = 1
        status_page = get_text(url % (str(now_rid)) )

        while not is_empty(status_page):
            info = get_submit(status_page)
            Rid = []
            for line in info:
                Rid.append(self.grab(line))

            now_rid = int(Rid[0]) + 1
            status_page = get_text(url % str(now_rid))
            
                       
    def grab(self, info):
        rid, date = info['rid'], info['date']
        print rid, date
        text = self.s.get('http://acm.hdu.edu.cn/%s' % rid).text
        pattern = re.compile('id=usercode style="display:none;text-align:left;">[\s\S]*</textarea>')
        result = pattern.search(text)
        code = result.group()[50:-11]

        code = re.sub('&lt;', '<', code)
        code = re.sub('&gt;', '>', code)
        code = re.sub('&amp;', '&', code)
        code = re.sub('&quot;', '\"', code)

        RunId = re.search('RunId...[0-9]*', text).group()[8:]
        Pid = re.search('showproblem.php.pid=....', text).group()[20:]
        Lang = '.java' if re.search('Language : Java', text) else '.cpp'
      
        head =  '******************************\n' \
                     '    Author : %s\n' \
                     '    Submit time : %s\n'\
                     '    Judge Status : Accepted\n' \
                     '    HDOJ Runid : %s\n' \
                     '    Problem id : %s\n' \
                     '    Exe.time : %s\n'  \
                     '    Exe.memory : %s\n' \
                     '    https://github.com/townboy\n' \
                '******************************\n\n\n' % (self.username, date, RunId, Pid, info['cpu'], info['memory'])
        date = re.sub(':', ' ', date)
        
        fp = codecs.open('../HDOJcode/' + Pid + ' ' + date + Lang, 'w', 'utf-8')

        fp.write(head)
        fp.write(code)
        fp.close()

        return RunId
        
    def start(self):
        if self.login():
            self.search_rid()
            print 'grab finish'
        else:
            print 'login failed'
            
if __name__ == '__main__':
    if len(sys.argv) >= 2:
        run = Grab(username = sys.argv[1], userpass = sys.argv[2])
        run.start()
    else:
        print 'please input username and userpass'
