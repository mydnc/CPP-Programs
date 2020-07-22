The task is to develop classes CMailBox and CMail, which simulate a mail box in a mail server.

CMailBox

This class represents one mail box. The mail box holds incoming mail (i.e. instances of CMail), the e-mails can be organized into folders. The CMailBox class is to be developed by you.

    CMail
        -This class represents one e-mail. 
        -The e-mail is represented by the date/time stamp, the address of the sender, the body of the mail, and an optional attachment. 
        -To represent these components, your implementation shall use classes CTimeStamp, std::string, CMailBody, and CAttach, respectively. 
        -The CMail class is to be developed by you.
    CTimeStamp
        -Is a simple container class that represent a time stamp (date and time). 
    CMailBody
        -Is another container, the class represents mail body. 
    CAttach
        -This class represents mail attachment.

CMailBox
-----------------------------------------------------------------------------------
The required interface is:

    constructor
        -creates an empty mailbox (no mail). 
        -Moreover, the new mailbox will contain one folder inbox.
    destructor, copy constructor, operator=
        -will have to be implemented if the default is not usable,
    Delivery (mail)
        -The method will be called when a new e-mail is to be stored into the mailbox. 
        -The new mail will be copied into the inbox folder. 
        -The method returns true (success), or false (failure, however, delivery shall not fail).
    NewFolder (name)
        -The method creates a new folder named name. 
        -The newly created folder shall be empty. 
        -The method returns true (success), or false (failure, folder of the name already exists). 
        -We assume one-level hierarchy of folders, i.e. folders cannot be nested. 
        -There are no restrictions on folder names.
    MoveMail (fromFld, toFld)
        -The method moves all e-mails from folder fromFld into folder toFld. 
        -The e-mails are moved, i.e. fromFld will be empty after a successful completion. 
        -The method returns true (success), or false (failure, from/to folder does not exist).
    ListMail (fld, from, to)
        -The method returns a list of e-mails selected from folder fld, moreover, the e-mails will be returned if the e-mail time stamp fits the time interval (from - to, both inclusive). 
        -If the folder does not exist, the method returns an empty list.
    ListAddr (from, to)
        -The method returns a set of e-mail addresses. 
        -The addresses will be selected from the e-mail that fits into the interval (from - to, both inclusive). 
        -The method shall search all folders. 
        -If no mail fits the time interval, the returned set will be empty.

CMail
-----------------------------------------------------------------------------------
The required interface is:

    constructor
        -creates an instance of e-mail based on the parameters. 
        -Parameter attach may be NULL indicating an e-mail without an attachment,
    destructor, copy constructor, operator =, ...
        -will be implement if the default are not usable,
    access methods (getters)
        -for individual fields (time stamp, sender, mail body, attachment), 
    output operator
        -displays the time stamp, sender, mail body and (optionally) the attachment. 
        -The objects representing individual fields do support output operators, the fields are to be separated by a single space (with an exception for the attachment, see the exact format in the enclosed archive). 

CTimeStamp
-----------------------------------------------------------------------------------
The interface is:

    constructor
        -creates an instance of the object based on year/month/day/hour/minute/second parameters,
    Compare (x)
        -The method compares the instance and parameter x. 
        -Return value is a negative number (instance is smaller than x), zero (instances represent identical time stamps), or positive (the instance is bigger than x). 
    output operator
        -displays the time stamp in format YYYY-MM-DD HH24:MI:SS. 

CMailBody
-----------------------------------------------------------------------------------
The interface is:

    constructor
        -creates an instance of the class, based on the length/content parameters,
    destructor, copy constructor, operator =, ...
        -the instances must correctly handle copying/moving,
    output operator
        -is provided in the attached file. The operator is intended for debugging only, it is not actually tested, 

CAttach
-----------------------------------------------------------------------------------
The interface is:

    constructor
        -creates an instance based on the contents (simplified). 
        -Next, the constructor initializes m_RefCnt, this member counts the references. 
        -The instance will be deleted when the number of references drops to 0 (m_RefCnt==0).
    AddRef
        -This method increases the number of references. When a reference to the object is created (such as when the constructor of CMail stores the pointer, or when getter Attach returns the reference), this method is to be called to increase the counter to match the number of actual references.
    Release
        -The method decreases the reference count. 
        -When the reference count drops to zero, the instance commits a suicide. 
        -The method will be when a reference to the instance is about to vanish, such as in the destructor of CMail. 
        -Similarly, Release needs to be called when a reference to attachment object (previously obtained via getter Attach) is to vanish.
    destructor
        -releases the resources allocated in the instance (simplified in the delivered implementation). 
        -Please note the destructor is private. The private destructor means two things. First, instances of CAttach cannot be allocated statically. Second, instances of CAttach cannot be deleted directly by delete. There is a good reason: an instance (possibly referenced from many other objects) cannot be deleted. Instead, the AddRef/Release mechanism must be used (thus the users of CAttach must follow the counted references).
    copy constructor, operator =, ...
        -these are private, thus cannot be used by other parts of the program.
    output operator
        -is delivered in the attached file
    mutable m_RefCnt
        -the mutable keyword allows modifications of m_RefCnt even from const methods.