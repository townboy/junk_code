# -*- coding:utf-8 -*-
import requests
import re
import codecs
import sys
import time

class Grab(object):
    def __init__(self, user, pwd):
        self.user = user
        self.pwd = pwd
        self.index_url = 'https://family.123u.com/'
        self.s = requests.session()
        self.login_url = 'https://family.123u.com/welcomepage?destination=uc/dynamic'
        self.like_url = 'https://family.123u.com/uc/dynamic/ajax/like?'

    def login(self):
        pass

    def get_build_id(self):
        r = self.s.get(self.index_url).text
        build_id = re.findall('form-\S{43}', r);
        return build_id[0]
      
    def start(self):
        self.build_id = self.get_build_id()
        print 'build_id is ' + str(self.build_id)

        data = { 'name' : self.user,
                 'pass' : self.pwd,
                 'form_build_id' : self.build_id,
                 'form_id' : 'user_login_block',
                 'op' : '登录',
                 'remember_me' : '1'
            }

        Login = self.s.post(self.login_url, data)

        self.click()
       
    def click(self):
        data = {'nid' : '20044'}
        self.s.post(self.like_url + str(int(time.time() ) ), data)
        
        
if __name__ == '__main__':
    user, pwd = raw_input('please input user pass!\n').split()
    print user, pwd
    run = Grab(user, pwd)
    run.start()
