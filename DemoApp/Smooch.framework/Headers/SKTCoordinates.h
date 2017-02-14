//
//  SKTCoordinates.h
//  Smooch
//
//  Copyright (c) 2017 Smooch Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SKTCoordinates : NSObject

/**
 *  The latitude in degrees. May be nil
 */
@property (nullable) NSNumber *latitude;

/**
 *  The longitude in degrees. May be nil
 */
@property (nullable) NSNumber *longitude;

/**
 *  @abstract Creates coordinates with the given latitude and longitude
 */
-(nonnull instancetype)initWithLatitude:(double)latitude longitude:(double)longitude;

@end
