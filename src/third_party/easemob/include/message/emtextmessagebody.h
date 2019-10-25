/************************************************************
 *  * EaseMob CONFIDENTIAL
 * __________________
 * Copyright (C) 2015 EaseMob Technologies. All rights reserved.
 * 
 * NOTICE: All information contained herein is, and remains
 * the property of EaseMob Technologies.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from EaseMob Technologies.
 */
//
//  EMTextMessageBody.h
//
//  Copyright (c) 2015年 EaseMob Inc. All rights reserved.
//

#ifndef __easemob__EMTextMessageBody__
#define __easemob__EMTextMessageBody__

#include <string>
#include "emmessagebody.h"

namespace easemob {

class EASEMOB_API EMTextMessageBody : public EMMessageBody
{
public:
    /**
      * \brief Text message body constructor.
      *
      * @param  The text.
      * @return NA
      */
    EMTextMessageBody(const std::string& = "");
    
    /**
      * \brief Copy constructor.
      *
      * @param  Another text message body.
      * @return NA
      */
    EMTextMessageBody(const EMTextMessageBody&);
    
    /**
      * \brief Assign operator overload.
      *
      * @param  Another text message body.
      * @return The text message body.
      */
    EMTextMessageBody& operator=(const EMTextMessageBody&);
    
    /**
      * \brief Class destructor.
      *
      * @param  NA
      * @return NA
      */
    virtual ~EMTextMessageBody();
    
    /**
      * \brief Get the text.
      *
      * @param  NA
      * @return The text.
      */
    const std::string& text() const;
    
private:
    virtual void dummy() const{}
    std::string mText;
    friend class EMTextMessageBodyPrivate;
};
    
typedef std::shared_ptr<EMTextMessageBody> EMTextMessageBodyPtr;

}
#endif /* defined(__easemob__EMTextMessageBody__) */
