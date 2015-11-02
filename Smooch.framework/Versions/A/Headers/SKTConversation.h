//
//  SKTConversation.h
//  Smooch
//
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SKTMessage.h"
#import "SKTMessageAction.h"
@protocol SKTConversationDelegate;

typedef void (^SKTImageUploadProgressBlock)(double progress);
typedef void (^SKTImageUploadCompletionBlock)(NSError *error, SKTMessage *message);

/**
 *  @discussion Represents various actions the user takes when interacting with Smooch UI components.
 */
typedef NS_ENUM(NSInteger, SKTAction) {
    /**
     *  The user has tapped on a Smooch in-app notification.
     */
    SKTActionInAppNotificationTapped,
    /**
     *  The user has tapped on a Smooch push notification.
     */
    SKTActionPushNotificationTapped
};

/**
 *  @abstract Notification that is fired when the count of unread messages changes. The notification object will be an instance of SKTConversation, of which you can then inspect the messageCount property.
 *
 *  @see SKTConversation
 */
extern NSString* const SKTConversationUnreadCountDidChangeNotification;

/**
 *  @abstract Notification that is fired when new messages are received from the server.
 *
 *  @discussion To inspect the messages, the userInfo dictionary contains an array of SKTMessage objects with key SKTConversationNewMessagesKey.
 *
 *  Example:
 *
 *  `NSArray* newMessages = notification.userInfo[SKTConversationNewMessagesKey];`
 *
 *  @see SKTMessage
 *  @see SKTConversationNewMessagesKey
 */
extern NSString* const SKTConversationDidReceiveMessagesNotification;

/**
 *  @abstract The key to use to retrieve new messages in SKTConversationDidReceiveMessagesNotification userInfo dictionary
 *
 *  @see SKTConversationDidReceiveMessagesNotification
 */
extern NSString* const SKTConversationNewMessagesKey;

/**
 *  @discussion The SKTConversation class provides an interface to interact with the current user's conversation. 
 *  
 *  To obtain an instance, use `[Smooch conversation]`. +initWithSettings: must have been called prior to retrieving the shared conversation object.
 *
 *  To send a message, use -sendMessage: with an SKTMessage object
 *
 *  Example:
 *
 *  `[[Smooch conversation] sendMessage:[[SKTMessage alloc] initWithText:@"Hello World!"]];`
 *
 *  A notification will be fired indicating the success or failure of the message. To subscribe to these notifications, use NSNotificationCenter.
 *
 *  Example:
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageUploaded:) name:SKTMessageUploadCompletedNotification object:nil];`
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageFailed:) name:SKTMessageUploadFailedNotification object:nil];`
 *
 *  @see SKTMessage
 *  @see Smooch
 */
@interface SKTConversation : NSObject

/**
 *  @abstract The array of SKTMessage objects representing the conversation.
 *
 *  @see SKTMessage
 */
@property(readonly) NSArray* messages;

/**
 *  @abstract The total number of messages in the conversation, including user-generated messages.
 */
@property(readonly) NSUInteger messageCount;

/**
 *  @abstract Count of unread messages in the conversation.
 *
 *  @discussion The primary use of this property is to be able to display an indicator / badge when the conversation has unread messages.
 */
@property(readonly) NSUInteger unreadCount;

/**
 *  @abstract A delegate object for receiving notifications related to the conversation.
 *
 *  @see SKTConversationDelegate
 */
@property(weak) id<SKTConversationDelegate> delegate;

/**
 *  @abstract Marks all unread messages as read.
 *
 *  @discussion Marks all unread messages as read, and notifies that the unread count changed.
 *
 *  @see SKTMessage
 */
-(void)markAllAsRead;

/**
 *  @abstract Adds a new message to the conversation.
 *
 *  @discussion For each message added using `sendMessage`, a notification will be fired indicating the success or failure status of the upload.
 *
 *  @see SKTMessageUploadFailedNotification
 *  @see SKTMessageUploadCompletedNotification
 */
-(void)sendMessage:(SKTMessage*)message;

/**
 *  @abstract Adds an image message to the conversation.
 *
 *  @discussion Use the progress block to track the progress of the upload. Progress is reported as a number between 0 and 1.
 *
 *  The completion block is called when the operation completes, either in success or failure. Both blocks are guaranteed to be called on the main thread.
 *
 *  In case of success, the error parameter will be nil, and the message parameter will contain the newly created message. The message will already be part of the messages array when this block is called.
 *
 *  In case of failure, the message parameter will be nil, and the error parameter will contain the error that occurred.
 *
 *  @param image The image to upload. Must not be nil.
 *  @param progressBlock Called to report progress updates. May be nil.
 *  @param completionBlock Called when the upload completes or fails. May be nil.
 */
-(void)sendImage:(UIImage *)image withProgress:(SKTImageUploadProgressBlock)progressBlock completion:(SKTImageUploadCompletionBlock)completionBlock;

/**
 *  @abstract Retries a message that failed to send.
 *
 *  @discussion The failed message will be removed from the messages array, and a new message will be constructed with the same text as the failed message. A notification will be fired indicating the success or failure status of the upload.
 *
 *  @see SKTMessageUploadFailedNotification
 *  @see SKTMessageUploadCompletedNotification
 */
-(void)retryMessage:(SKTMessage*)failedMessage;

@end

/**
 *  @discussion Delegate protocol for events related to the conversation.
 *
 *  Creating a delegate is optional, and may be used to receive callbacks when important changes happen in the conversation.
 *
 *  Delegate methods are guaranteed to be called from the main thread.
 */
@protocol SKTConversationDelegate <NSObject>

@optional
/**
 *  @abstract Notifies the delegate of a change in unread message count.
 *  
 *  @discussion Called when conversation data is fetched from the server, or when the user enters the conversation screen.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param unreadCount The new number of unread messages.
 */
-(void)conversation:(SKTConversation*)conversation unreadCountDidChange:(NSUInteger)unreadCount;

/**
 *  @abstract Asks the delegate if an in-app notification should be shown for a message.
 *
 *  @discussion Called when a new message is received, right before the in-app notification is to be shown for that message. To show your own in-app notification, return NO from this method, and use the SKTMessage object to construct your view.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param message The message that will be displayed in the notification.
 *
 *  @return YES to allow Smooch to present the notification. NO to suppress the notification, and perform custom handling.
 *
 *  @see SKTMessage
 */
-(BOOL)conversation:(SKTConversation*)conversation shouldShowInAppNotificationForMessage:(SKTMessage*)message;

/**
 *  @abstract Asks the delegate if the conversation should show for the given action.
 *
 *  @discussion Called when the user performs an action that causes the conversation screen to show. Return NO to cancel the display of the conversation screen and perform your own handling of the action.
 *
 *  @param conversation The conversation object.
 *  @param message The action the user has taken.
 *
 *  @return YES to allow default handling. NO to suppress the conversation screen, and perform custom handling.
 *
 *  @see SKTAction
 */
-(BOOL)conversation:(SKTConversation*)conversation shouldShowForAction:(SKTAction)action;

/**
 *  @abstract Notifies the delegate of new incoming messages.
 *
 *  @discussion Called when new messages are received from the server.
 *
 *  @param conversation The conversation object.
 *  @param message An array of SKTMessage objects representing the new messages.
 *
 *  @see SKTMessage
 */
-(void)conversation:(SKTConversation*)conversation didReceiveMessages:(NSArray*)messages;

@end
