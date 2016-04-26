//
//  SKTMessageAction.h
//  Smooch
//
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @abstract Type for a link action.
 */
extern NSString* const SKTMessageActionTypeLink;

/**
 *  @abstract Type for a buy action.
 */
extern NSString* const SKTMessageActionTypeBuy;

/**
 *  @abstract Type for a postback action.
 */
extern NSString* const SKTMessageActionTypePostback;

/**
 *  @abstract Offered state for a buy message. The user has not yet completed the transaction.
 */
extern NSString* const SKTMessageActionStateOffered;

/**
 *  @abstract Paid state for a buy message. The user has completed the transaction and payment was successful.
 */
extern NSString* const SKTMessageActionStatePaid;

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
@property(readonly) NSString* actionId;

/**
 *  @abstract The type of action.
 *
 *  @discussion Valid types include `SKTMessageActionTypeLink` for regular actions, and `SKTMessageActionTypeBuy` for buy actions.
 */
@property(readonly) NSString* type;

/**
 *  @abstract The text to display as a descriptor for the action.
 *
 *  @discussion May not be nil.
 */
@property(readonly) NSString* text;

/**
 *  @abstract The URI to navigate to if the user interacts with the action.
 *
 *  @discussion May not be nil.
 */
@property(readonly) NSURL* uri;

/**
 *  @abstract Metadata associated with the action.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(readonly) NSDictionary* metadata;

#pragma mark - Buy actions

/**
 *  @abstract The purchase state of the action
 *
 *  @discussion This property is only non-nil for actions of type `SKTMessageActionTypeBuy`. Valid states include `SKTMessageActionStateOffered` and `SKTMessageActionStatePaid`.
 */
@property(readonly) NSString* state;

/**
 *  @abstract The amount of money to charge for the action.
 *
 *  @discussion This property is only valid for actions of type `SKTMessageActionTypeBuy`. For USD, this value is in cents.
 */
@property(readonly) long amount;

/**
 *  @abstract The currency in which the `amount` is expressed.
 *
 *  @discussion This property is only valid for actions of type `SKTMessageActionTypeBuy`.
 */
@property(readonly) NSString* currency;

@end
