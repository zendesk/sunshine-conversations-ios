//
//  SKTMessageAction.h
//  Smooch
//

#import <Foundation/Foundation.h>

/**
 *  @abstract Type for a link action.
 */
extern NSString* _Nonnull const SKTMessageActionTypeLink;

/**
 *  @abstract Type for a webview action.
 */
extern NSString* _Nonnull const SKTMessageActionTypeWebview;

/**
 *  @abstract Type for a buy action.
 */
extern NSString* _Nonnull const SKTMessageActionTypeBuy;

/**
 *  @abstract Type for a postback action.
 */
extern NSString* _Nonnull const SKTMessageActionTypePostback;

/**
 *  @abstract Type for a reply action
 */
extern NSString* _Nonnull const SKTMessageActionTypeReply;

/**
 *  @abstract Type for a location request
 */
extern NSString* _Nonnull const SKTMessageActionTypeLocationRequest;

/**
 *  @abstract Offered state for a buy message. The user has not yet completed the transaction.
 */
extern NSString* _Nonnull const SKTMessageActionStateOffered;

/**
 *  @abstract Paid state for a buy message. The user has completed the transaction and payment was successful.
 */
extern NSString* _Nonnull const SKTMessageActionStatePaid;

/**
 *  @abstract A full-sized webview
 */
extern NSString* _Nonnull const SKTMessageActionWebviewSizeFull;

/**
 *  @abstract A tall-sized webview
 */
extern NSString* _Nonnull const SKTMessageActionWebviewSizeTall;

/**
 *  @abstract A compact-sized webview
 */
extern NSString* _Nonnull const SKTMessageActionWebviewSizeCompact;

/**
 *  @abstract An action associated to a particular SKTMessage.
 *
 *  Actions are rendered as buttons in the Smooch conversation screen, and may be of type `SKTMessageActionTypeLink`, `SKTMessageActionTypeBuy` or `SKTMessageActionTypePostback`.
 *
 *  @see SKTMessage
 */
@interface SKTMessageAction : NSObject

/**
 *  @abstract The unique identifier representing the action.
 */
@property(readonly, nullable) NSString* actionId;

/**
 *  @abstract The type of action.
 *
 *  @discussion Valid types include `SKTMessageActionTypeLink` for regular actions, and `SKTMessageActionTypeBuy` for buy actions.
 */
@property(nullable) NSString* type;

/**
 *  @abstract The text to display as a descriptor for the action.
 *
 *  @discussion May not be nil.
 */
@property(nullable) NSString* text;

/**
 *  @abstract The URI to navigate to if the user interacts with the action.
 *
 *  @discussion May not be nil if message is of type `SKTMessageActionTypeLink` or `SKTMessageActionTypeWebview`
 */
@property(nullable) NSURL* uri;

/**
 *  @abstract The size of a webview
 *
 *  @discussion May not be nil if message is of type `SKTMessageActionTypeWebview`
 */
@property(nullable, copy) NSString* size;

/**
 *  @abstract Metadata associated with the action.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(nullable) NSDictionary* metadata;

/**
 *  @abstract Icon to display with a reply
 *
 *  @discussion An icon to render next to the reply option
 */
@property(nullable) NSString* iconUrl;

/**
 *  @abstract The payload of actions with type SKTMessageActionTypeReply or SKTMessageActionTypePostback
 *
 *  @discussion The payload of actions with type SKTMessageActionTypeReply or SKTMessageActionTypePostback, if applicable. May be nil
 */
@property(nullable) NSString* payload;

#pragma mark - Buy actions

/**
 *  @abstract The purchase state of the action
 *
 *  @discussion This property is only non-nil for actions of type `SKTMessageActionTypeBuy`. Valid states include `SKTMessageActionStateOffered` and `SKTMessageActionStatePaid`.
 */
@property(nullable) NSString* state;

/**
 *  @abstract The amount of money to charge for the action.
 *
 *  @discussion This property is only valid for actions of type `SKTMessageActionTypeBuy`. For USD, this value is in cents.
 */
@property long amount;

/**
 *  @abstract The currency in which the `amount` is expressed.
 *
 *  @discussion This property is only valid for actions of type `SKTMessageActionTypeBuy`.
 */
@property(nullable) NSString* currency;

@end
