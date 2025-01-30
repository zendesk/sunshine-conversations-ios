//
//  SKTMessage.h
//  Smooch
//

#import <UIKit/UIKit.h>
#import "SKTCoordinates.h"
#import "SKTDisplaySettings.h"

/**
 *  @abstract Notification that is fired when a message fails to upload.
 */
extern NSString* _Nonnull const SKTMessageUploadFailedNotification;

/**
 *  @abstract Notification that is fired when a message uploads successfully.
 */
extern NSString* _Nonnull const SKTMessageUploadCompletedNotification;

/**
 *  @abstract A type of message that contains an image, text, and/or action buttons
 */
extern NSString* _Nonnull const SKTMessageTypeImage;

/**
 *  @abstract A type of message that contains text and/or action buttons
 */
extern NSString* _Nonnull const SKTMessageTypeText;

/**
 *  @abstract A type of message that contains a location
 */
extern NSString* _Nonnull const SKTMessageTypeLocation;

/**
 *  @abstract A type of message that contains a file and/or text
 */
extern NSString* _Nonnull const SKTMessageTypeFile;

/**
 *  @abstract A type of message that contains a horizontally scrollable set of items
 */
extern NSString* _Nonnull const SKTMessageTypeCarousel;

/**
 *  @abstract A type of message that contains a vertically scrollable set of items
 */
extern NSString* _Nonnull const SKTMessageTypeList;

/**
 *  @discussion Upload status of an SKTMessage.
 *
 *  @see SKTMessage
 */
typedef NS_ENUM(NSInteger, SKTMessageUploadStatus) {
    /**
     *  A user message that has not yet finished uploading.
     */
    SKTMessageUploadStatusUnsent,
    /**
     *  A user message that failed to upload.
     */
    SKTMessageUploadStatusFailed,
    /**
     *  A user message that was successfully uploaded.
     */
    SKTMessageUploadStatusSent,
    /**
     *  A message that did not originate from the current user.
     */
    SKTMessageUploadStatusNotUserMessage
};

/// A class representing a message.
@interface SKTMessage : NSObject <NSSecureCoding>

/**
 *  @abstract Create a message with the given text. The message will be owned by the current user.
 */
-(nonnull instancetype)initWithText:(nonnull NSString*)text;

/**
 *  @abstract Create a message with the given text, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithText:(nonnull NSString *)text payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract Create a message with the given coordinates, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithCoordinates:(nonnull SKTCoordinates *)coordinates payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract The unique identifier of the message. May be nil if a unique identifier has not been generated for this message
 */
@property(readonly, nullable) NSString* messageId;

/**
 *  @abstract The text content of the message. May be nil if mediaUrl or actions are provided
 */
@property(nullable) NSString* text;

/**
 *  @abstract The text fallback to display for message types not supported by the SDK. May be nil
 */
@property(nullable) NSString* textFallback;

/**
 *  @abstract The displayName of the author. This property may be nil if no displayName could be determined.
 */
@property(nullable) NSString* displayName;

/**
 *  @abstract The url for the author's avatar image. May be nil
 */
@property(nullable) NSString* avatarUrl;

/**
 *  @abstract The date and time the message was sent
 */
@property(nullable) NSDate *date;

/**
 *  @abstract Returns YES if the message originated from the user, or NO if the message comes from the app team.
 */
@property (nonatomic) BOOL isFromCurrentUser;

/**
 *  @abstract The upload status of the message.
 *
 *  @see SKTMessageStatus
 */
@property(readonly) SKTMessageUploadStatus uploadStatus;

/**
 *  @abstract An array of SKTMessageAction objects representing the actions associated with this message (if any)
 *
 *  @discussion This array may be nil or empty, so check the length of the array to know if a message has actions or not.
 *
 *  @see SKTMessageAction
 */
@property(readonly, nullable) NSArray* actions;

/**
 *  @abstract An array of SKTMessageItem objects representing the items associated with this message
 *
 *  @discussion Only messages of type `SKTMessageTypeCarousel` and `SKTMessageTypeList` contain items.
 *
 *  @see SKTMessageItem
 */
@property(readonly, nullable) NSArray* items;

/**
 *  @abstract The url to the media asset, if applicable. Returns nil if the message is not an image or file message.
 */
@property(nullable) NSString* mediaUrl;

/**
 *  @abstract The attachment id, if applicable. Returns nil if the message doesn't contains private attachment
 */
@property(nullable) NSString* attachmentId;

/**
 *  @abstract The size of the media asset in bytes. May be nil.
 */
@property(nullable) NSNumber* mediaSize;

/**
 *  @abstract The type the message.
 *
 *  @discussion Valid types include SKTMessageTypeText, SKTMessageTypeImage, and SKTMessageTypeLocation
 */
@property(nullable) NSString* type;

/**
 *  @abstract Coordinates for a location for a message of type SKTMessageTypeLocation
 */
@property(readonly, nullable) SKTCoordinates *coordinates;

/**
 *  @abstract Settings to adjust the layout of a message of type SKTMessageTypeCarousel
 *
 *  @see SKTDisplaySettings
 */
@property(readonly, nullable) SKTDisplaySettings *displaySettings;

/**
 *  @abstract The role of the message.
 *
 *  @discussion Valid roles include `appUser`, `business`, and `whisper`. Messages created with -initWithText: have role of `appUser`.
 */
@property(readonly, nullable) NSString* role;

/**
 *  @abstract Metadata associated with the message.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(nullable) NSDictionary* metadata;

/**
 *  @abstract The payload of an action with type SKTMessageActionTypeReply
 *
 *  @discussion The payload of a SKTMessageActionTypeReply, if applicable. May be nil
 */
@property(nullable) NSString* payload;

/**
 *  @abstract Array of subroles associated with an author.
 *  The initial purpose of this array was to indicate if a message was generated by AI.
 *  E.g. "subroles" : ["AI"]
 *
 *  @discussion May be nil or empty.
 */
@property(readonly, nullable) NSArray<NSString*>* subroles;

@end
