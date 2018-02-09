//
//  SKTConversation.h
//  Smooch
//

#import <Foundation/Foundation.h>
#import "SKTMessage.h"
#import "SKTMessageAction.h"
#import "SKTMessageItem.h"
#import "SKTConversationActivity.h"

NS_ASSUME_NONNULL_BEGIN
@protocol SKTConversationDelegate;

typedef void (^SKTImageUploadProgressBlock)(double progress);
typedef void (^SKTImageUploadCompletionBlock)(NSError* _Nullable error, SKTMessage* _Nullable message);

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
 *  @abstract Posted when the count of unread messages changes. The notification object will be an instance of SKTConversation, of which you can then inspect the messageCount property.
 *
 *  @see SKTConversation
 */
extern NSString* const SKTConversationUnreadCountDidChangeNotification;

/**
 *  @abstract Posted when an image upload begins.
 *
 *  @discussion The userInfo dictionary contains the UIImage to upload. Use SKTConversationImageKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SKTConversationImageKey
 */
extern NSString* const SKTConversationImageUploadDidStartNotification;

/**
 *  @abstract Posted when an image upload receives a progress update.
 *
 *  @discussion The userInfo dictionary contains the UIImage being uploaded, as well as an NSNumber reflecting the current progress. Use SKTConversationImageKey and SKTConversationProgressKey to access these values.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SKTConversationImageKey
 *  @see SKTConversationProgressKey
 */
extern NSString* const SKTConversationImageUploadProgressDidChangeNotification;

/**
 *  @abstract Posted when an image upload completes, either in success or failure.
 *
 *  @discussion The userInfo dictionary contains the UIImage that was uploaded. Use SKTConversationImageKey to access this value.
 *
 *  If the upload succeeded, the userInfo dictionary will also include the SKTMessage instance of the new message. Use SKTConversationMessageKey to access this value.
 *  If the upload failed, the userInfo dictionary will include the NSError that occurred. Use SKTConversationErrorKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SKTMessage
 *  @see SKTConversationImageKey
 *  @see SKTConversationMessageKey
 *  @see SKTConversationErrorKey
 */
extern NSString* const SKTConversationImageUploadCompletedNotification;

/**
 *  @abstract Posted when new messages are received from the server.
 *
 *  @discussion The userInfo dictionary contains an NSArray of SKTMessage objects. Use SKTConversationNewMessagesKey to access this value.
 *
 *  @see SKTMessage
 *  @see SKTConversationNewMessagesKey
 */
extern NSString* const SKTConversationDidReceiveMessagesNotification;

/**
 *  @abstract Posted when an operation to load previous messages in a conversation has been completed
 *
 *  @discussion This notification is posted as the result of [SKTConversation loadPreviousMessages]
 *
 *  If the operation succeeded, the object returned by this notification will include the updated array of messages
 *  If the operation failed, the userInfo dictionary will contain an "error" object with the response error
 *
 *  @see SKTMessage
 *  @see SKTConversationPreviousMessagesKey
 */
extern NSString* const SKTConversationDidReceivePreviousMessagesNotification;

/**
 *  @abstract Posted when a conversation activity has been created, such as typing start/stop
 *
 *  @see SKTConversationActivity
 *  @see SKTConversationActivityKey
 */
extern NSString* const SKTConversationDidReceiveActivityNotification;

/**
 *  @abstract A key whose value is an NSArray of SKTMessage objects.
 *
 *  @discussion This key is used with SKTConversationDidReceiveMessagesNotification notification.
 *
 *  @see SKTConversationDidReceiveMessagesNotification
 */
extern NSString* const SKTConversationNewMessagesKey;

/**
 *  @abstract A key whose value is an NSArray of SKTMessage objects
 *
 *  @discussion This key is used with SKTConversationDidReceivePreviousMessagesNotification notification
 *
 *  @see SKTConversationDidReceivePreviousMessagesNotification
 */
extern NSString* const SKTConversationPreviousMessagesKey;

/**
 *  @abstract A key whose value is a UIImage which represents an image being uploaded.
 *
 *  @discussion This key is used with SKTConversationImageUploadDidStartNotification, SKTConversationImageUploadProgressDidChangeNotification, and SKTConversationImageUploadCompletedNotification notifications.
 *
 *  @see SKTConversationImageUploadDidStartNotification
 *  @see SKTConversationImageUploadProgressDidChangeNotification
 *  @see SKTConversationImageUploadCompletedNotification
 */
extern NSString* const SKTConversationImageKey;

/**
 *  @abstract A key whose value is an NSError.
 *
 *  @discussion This key is used with SKTConversationImageUploadCompletedNotification notification.
 *
 *  @see SKTConversationImageUploadCompletedNotification
 */
extern NSString* const SKTConversationErrorKey;

/**
 *  @abstract A key whose value is an SKTMessage object representing the newly created message.
 *
 *  @discussion This key is used with SKTConversationImageUploadCompletedNotification notification.
 *
 *  @see SKTConversationImageUploadCompletedNotification
 */
extern NSString* const SKTConversationMessageKey;

/**
 *  @abstract A key whose value is an NSNumber reflecting the current progress of an image upload.
 *
 *  @discussion This key is used with SKTConversationImageUploadProgressDidChangeNotification notification.
 *
 *  @see SKTConversationImageUploadProgressDidChangeNotification
 */
extern NSString* const SKTConversationProgressKey;

/**
 *  @abstract A key whose value is a SKTConversationActivity object representing the newly created activity
 *
 *  @discussion This key is used with SKTConversationDidReceiveActivityNotification notification.
 *
 *  @see SKTConversationDidReceiveActivityNotification
 */
extern NSString* const SKTConversationActivityKey;

/**
 *  @discussion The SKTConversation class provides an interface to interact with the current user's conversation.
 *
 *  To obtain an instance, use `[Smooch conversation]`. +initWithSettings:completionHandler: must have been called prior to retrieving the shared conversation object.
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
@property(readonly, nullable) NSArray* messages;

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
 *  @abstract Date when the business last read the user messages
 */
@property(readonly) NSDate *appMakerLastRead;

/**
 *  @abstract A delegate object for receiving notifications related to the conversation.
 *
 *  @see SKTConversationDelegate
 */
@property(weak, nullable) id<SKTConversationDelegate> delegate;


/**
 *  @abstract Boolean representing whether there are previous messages in the conversation that can be fetched or not
 *
 *  @discussion Returns YES if there are previous messages in the conversation, NO otherwise. For fetching previous messages, use [SKTConversation loadPreviousMessages]
 */
@property(readonly) BOOL hasPreviousMessages;

/**
 *  @abstract Marks all unread messages as read.
 *
 *  @discussion Marks all unread messages as read, and notifies that the unread count changed.
 *
 *  @see SKTMessage
 */
-(void)markAllAsRead;

/**
 *  @abstract Loads previous messages for this conversation, if any
 *
 *  @dicussion Will get previous messages for this conversation based on the timestamp of the current oldest message and will notify the delegate of new incoming messages through [SKTConversationDelegate conversation:didReceivePreviousMessages:]
 */
-(void)loadPreviousMessages;

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
-(void)sendImage:(UIImage *)image withProgress:(nullable SKTImageUploadProgressBlock)progressBlock completion:(nullable SKTImageUploadCompletionBlock)completionBlock;

/**
 *  @abstract Sends a postback to the server.
 *
 *  @discussion The completion block is called when the operation completes, either in success or failure.
 *
 *  In case of success, the error parameter will be nil.
 *
 *  In case of failure, the error parameter will contain the error that occurred.
 *
 *  @param messageAction The messageAction for which to send the postback. Must not be nil.
 *  @param completionBlock Called when the postback completes or fails. May be nil.
 */
-(void)postback:(SKTMessageAction*)messageAction completion:(nullable void (^)(NSError* _Nullable error))completionBlock;

/**
 *  @abstract Retries a message that failed to send.
 *
 *  @discussion The failed message will be removed from the messages array, and a new message will be constructed with the same text as the failed message. A notification will be fired indicating the success or failure status of the upload.
 *
 *  @see SKTMessageUploadFailedNotification
 *  @see SKTMessageUploadCompletedNotification
 */
-(void)retryMessage:(SKTMessage*)failedMessage;

/**
 *  @abstract Notify the server that the user is typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  Typing updates are automatically throttled, so you may call this method as often as necessary. The typing stop event will automatically fire 10 seconds after the most recent call to this method.
 */
-(void)startTyping;

/**
 *  @abstract Notify the server that the user has finished typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  If the user was not flagged as typing recently, this method will result in a no-op.
 */
-(void)stopTyping;

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
 *  @param action The action the user has taken.
 *  @param info An instance of NSDictionary with a `message` object with the latest SKTMessage represented as an NSDictionary
 *
 *  @return YES to allow default handling. NO to suppress the conversation screen, and perform custom handling.
 *
 *  @see SKTAction
 */
-(BOOL)conversation:(SKTConversation*)conversation shouldShowForAction:(SKTAction)action withInfo:(nullable NSDictionary *) info;

/**
 *  @abstract Gives the delegate the option to modify a message before it is sent
 *
 *  @discussion Called when a message is about to be sent to give the delegate the option of modify or decorate its content (i.e. add metadata) before sending to Smooch
 *
 *  @return the message to be sent
 */
-(SKTMessage *)conversation:(SKTConversation*)conversation willSendMessage:(SKTMessage *)message;

/**
 *  @abstract Gives the delegate the option to modify a message before it is displayed. If nil is returned the message will be hidden
 *
 *  @discussion Called when a message is about to be displayed to the user to give the delegate the option of modifying its content before display or hide it
 *
 *  @return the message to be displayed. If nil, the message won't get displayed
 */
-(nullable SKTMessage *)conversation:(SKTConversation*)conversation willDisplayMessage:(SKTMessage *)message;

/**
 *  @abstract Notifies the delegate of new incoming messages.
 *
 *  @discussion Called when new messages are received from the server.
 *
 *  @param conversation The conversation object.
 *  @param messages An array of SKTMessage objects representing the new messages.
 *
 *  @see SKTMessage
 */
-(void)conversation:(SKTConversation*)conversation didReceiveMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate when older messages in the conversation history have been received
 *
 *  @dicussion Called when older messages in the conversation history are received from the server
 *
 *  @param conversation The conversation object
 *  @param messages The messages that have been fetched
 */
-(void)conversation:(SKTConversation*)conversation didReceivePreviousMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate of new conversation activity
 *
 *  @dicussion Called when a new activity is received from the server
 *
 *  @param conversation The conversation object
 *  @param activity The activity that was received
 */
-(void)conversation:(SKTConversation *)conversation didReceiveActivity:(SKTConversationActivity *)activity;

/**
 *  @abstract Asks the delegate if default handling should be performed for a message action.
 *
 *  @discussion Called when the user taps a message action.
 *
 *  @return YES to allow default handling. NO to perform custom handling.
 */
-(BOOL)conversation:(SKTConversation *)conversation shouldHandleMessageAction:(SKTMessageAction*)action;

/**
 *  @abstract Notifies the delegate when the conversation is about to be presented.
 *
 *  @discussion Called in the viewWillAppear: method of the conversation view controller.
 */
-(void)conversation:(SKTConversation *)conversation willShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when presentation of the conversation completes.
 *
 *  @discussion Called in the viewDidAppear: method of the conversation view controller.
 */
-(void)conversation:(SKTConversation *)conversation didShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when the conversation is about to be dismissed.
 *
 *  @discussion Called in the viewWillDisappear: method of the conversation view controller.
 */
-(void)conversation:(SKTConversation *)conversation willDismissViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when dismissal of the conversation completes.
 *
 *  @discussion Called in the viewDidDisappear: method of the conversation view controller.
 */
-(void)conversation:(SKTConversation *)conversation didDismissViewController:(UIViewController*)viewController;

@end
NS_ASSUME_NONNULL_END
