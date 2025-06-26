//
//  SKTMessageItem.h
//  Smooch
//

#import <Foundation/Foundation.h>

/// A class representing a message item.
@interface SKTMessageItem : NSObject

/**
 *  @abstract The title of the item
 */
@property(copy, nullable) NSString *title;

/**
 *  @abstract Array of `SKTMessageAction` buttons
 *
 *  @see SKTMessageAction
 */
@property(nullable) NSArray *actions;

/**
 *  @abstract The text description, or subtitle
 */
@property(copy, nullable) NSString *itemDescription;

/**
 *  @abstract The image URL to be shown in the item
 */
@property(copy, nullable) NSString *mediaUrl;

/**
 *  @abstract The mediaType of the `mediaUrl`
 */
@property(copy, nullable) NSString *mediaType;

/**
 *  @abstract Metadata associated with the message item.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(nullable) NSDictionary* metadata;

@end
