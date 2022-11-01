//
//  SKTConversationListDelegate.h
//  Smooch
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @discussion Delegate protocol for events related to the conversation list and create conversation
 *
 *  Creating a delegate is optional, and may be used to receive callbacks.
 *
 */
@protocol SKTConversationListDelegate <NSObject>

@required

/**
 *  @abstract Asks the delegate if it wants to create it's own create conversation flow.
 *
 *  @discussion Called when a user taps the 'New Conversation' button on the SDK Conversation List screen.
 *
 *  @return YES/TRUE indicates that the SDK should NOT create a conversation.
 */
- (BOOL)shouldCreateCustomConversationFlow;

@optional

/**
 *  @abstract Notifies the delegate that a user has tapped the 'New Conversation' button on the SDK Conversation List screen.
 *
 *  @discussion Called from the main thread when a user taps the 'New Conversation' button on the SDK Conversation List screen.
 *
 */
- (void)conversationListDidSelectCreateConversation;

@end
NS_ASSUME_NONNULL_END
