//
//  RPMainContentView.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/19/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPMainContentView.h"

@implementation RPMainContentView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self initializator];
    }
    return self;
}

-(void)initializator
{
    self.navBar = [[UINavigationBar alloc] init];
    
    [self addSubview:self.navBar];
    
    self.label = [[UILabel alloc] init];
    self.label.text = @"You can integrate SupportKit with a simple button press, or with a gesture (give your phone a shake!)";
    self.label.textAlignment = NSTextAlignmentCenter;
    self.label.font = [UIFont systemFontOfSize:20];
    self.label.numberOfLines = 0;
    
    [self addSubview:self.label];
    
    self.button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [self.button setTitle:@"I Need Support" forState:UIControlStateNormal];
    
    [self addSubview:self.button];
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    
    self.navBar.frame = CGRectMake(0, 0, self.bounds.size.width, [self getNavBarHeight]);
    
    self.label.frame = CGRectMake(0,0, self.bounds.size.width - 100, 500);
    [self.label sizeToFit];
    self.label.center = CGPointMake(CGRectGetMidX(self.bounds), CGRectGetMidY(self.bounds) - 30);
    
    self.button.frame = CGRectMake(0,CGRectGetMaxY(self.label.frame) + 10,200,44);
    [self.button sizeToFit];
    self.button.center = CGPointMake(CGRectGetMidX(self.bounds), self.button.center.y);
}

-(CGFloat)getNavBarHeight
{
    int height = 44;
    
    if(UIDeviceOrientationIsLandscape([UIDevice currentDevice].orientation) && UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone){
        height = 32;
    }
    
    if(floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_6_1){
        height += 20;
    }
    
    return height;
}

@end
