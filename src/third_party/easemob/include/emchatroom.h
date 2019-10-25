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

#ifndef __easemob__emchatroom__
#define __easemob__emchatroom__

#include <string>
#include <memory>

#include "embaseobject.h"

namespace easemob
{
class EMChatroomPrivate;
class EMChatroomManager;
class EMDatabase;
class EASEMOB_API EMChatroom : public EMBaseObject
{
public:
    typedef enum
    {
        BE_KICKED,      //User is kicked out by the chatroom owner
        DESTROYED       //Chatroom was destroyed by the chatroom owner.
    } EMChatroomLeaveReason;

    virtual ~EMChatroom();
    
    /**
      * \brief Get chatroom's ID.
      *
      * @param  NA
      * @return Chatroom's ID.
      */
    const std::string& chatroomId() const;
    
    /**
      * \brief Get chatroom's subject.
      *
      * @param  NA
      * @return Chatroom's subject。
      */
    const std::string& chatroomSubject() const;
    
    /**
      * \brief Get chatroom's description.
      *
      * @param  NA
      * @return Chatroom's description.
      */
    const std::string& chatroomDescription() const;

    const std::string& owner();
    
private:
    /**
      * \brief Constructor.
      *
      * Note: User can‘t directly create a chatroom.
      * @param  Chatroom's ID
      * @return NA.
      */
    EMChatroom(const std::string &chatroomId);
    EMChatroom(const EMChatroom&);
    EMChatroom& operator=(const EMChatroom&);
    
    EMChatroomPrivate *mPrivate;
    friend EMChatroomManager;
    friend EMDatabase;
};

typedef std::shared_ptr<EMChatroom> EMChatroomPtr;

}

#endif /* defined(__easemob__emchatroom__) */
