import win32com.client

def docpw(doc, name, pw):
    try:
        pw = str(pw)
        docx = doc.Document.Open(name,False,True,None,PasswordDocument=pw)
        print('文档密码：{}'.format(pw))
        docx.Close()
        return True
    except:
        return False
    
if __name__=='__main__':
    p = 0
    doc = win32com.client.Dispatch('Word.Application')
    doc.Visible=1
    doc.DisplayAlerts=0
    print("start")
    while True:
        isdone = docpw(doc,r'word.docx',p)
        if isdone:
            break



