#!/bin/sh

create()
{
                echo "Enter address book name"
                read ab
                res=`ls | grep $ab | wc -w`
                
                if  [  $res -gt 0 ]
                then
                             echo "Error: File is already existing!"
                else
                             touch $ab
                fi            
 }
 
 display()
{
                echo "Enter address book name"
                read ab
                
                res=`ls | grep $ab | wc -w`
                if  [  $res -gt 0 ]
                then
                             cat $ab
                else
                            echo "Error: File does not exist!"
                fi            
 }
 
 insert()
{
                echo "Enter address book name"
                read ab
                
                res=`ls | grep $ab | wc -w`
                if [ $res -gt 0 ]
                then
                             echo "Enter email"
                             read email
                             len=`cat $ab | grep $email | wc -w`
                             if [ $len -gt 0 ]
                             then
                                       echo "Error: email is already existing!"
                              else
                                       echo "Enter First name, Last name, Mobile number"
                                       read fname lname mobile
                                       
                                       record=`echo $fname $lname $email $mobile`
                                       echo $record >> $ab
                                       echo "Record Inserted!"
                               fi
                else
                            echo "Error: File does not exist!"
                fi            
 }
 
  modify()
{
                echo "Enter address book name"
                read ab
                
                res=`ls | grep $ab | wc -w`
                if  [ $res -gt 0 ]
                then
                             echo "Enter email"
                             read email
                             len=`cat $ab | grep $email | wc -w`
                             if [ $len -gt 0 ]
                             then
                                      echo "Enter First name, Last name, Mobile number"
                                       read fname lname mobile
                                       new=`echo $fname $lname $email $mobile`
                                       old=`cat $ab | grep $email`
                                       
                                       echo "Old Record: $old"
                                       echo "New Record: $new"
                                       sed  -i s/"$old"/"$new"/g $ab
                                       echo "Record Modified!" 
                              else
                                       echo "Error: email does not exist!"
                               fi
                else
                            echo "Error: File does not exist!"
                fi            
 }
 
 delete()
{
                echo "Enter address book name"
                read ab
                
                res=`ls | grep $ab | wc -w`
                if  [  $res -gt 0  ]
                then
                             echo "Enter email"
                             read email
                             len=`cat $ab | grep $email | wc -w`
                             if [ $len -gt 0 ]
                             then
                                       old=`cat $ab | grep $email`
                                       sed  -i s/"$old"//g $ab
                                       sed -i  /^$/d $ab
                                       echo "Record Deleted!" 
                              else
                                       echo "Error: email does not exist!"
                               fi
                else
                            echo "Error: File does not exist!"
                fi            
 }
 
 while [  true  ]
 do
                      echo "*****************MENU*********************"
                      echo "1. Create"
                      echo "2. Display"
                      echo "3. Insert"
                      echo "4. Modify"
                      echo "5. Delete"
                      echo "7. Exit"
                      
                      echo "Enter Your Choice"
                      read choice
                      
                      case $choice in
                                      1) create ;;
                                      2) display ;;
                                      3) insert ;;
                                      4) modify ;;
                                      5) delete ;;
                                      7) exit ;;
                                      *) echo "Wrong Choice!" ;;
                      esac         
done 

