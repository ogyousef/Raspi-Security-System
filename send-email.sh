#!/bin/bash

Account='cs3307-group21@outlook.com'
Password='safepassword123456'   
FromName="Group 21 Security"
FromAddress="cs3307-group21@outlook.com"
ToName="$2"
ToAddress="$3"
Subject="Security Breach Detected"
SMTP="smtp.office365.com"
Port="587"
Message= "Hello"
File="$1"
MIMEType=`file --mime-type "$File" | sed 's/.*: //'`

curl -v --url smtp://$SMTP:$Port --ssl-reqd  --mail-from $FromAddress --mail-rcpt $ToAddress  --user $Account:$Password -F '=(;type=multipart/mixed' -F "=$Message;type=text/plain" -F "file=@$File;type=$MIMEType;encoder=base64" -F '=)' -H "Subject: $Subject" -H "From: $FromName <$FromAddress>" -H "To: $ToName <$ToAddress>"


