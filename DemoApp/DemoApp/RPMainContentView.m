//
//  RPMainContentView.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/19/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPMainContentView.h"
#import "RPRoundedButton.h"

static const int kLogoBottomPadding = 15;
static const int kFooterTextBottomPadding = 20;

@interface RPMainContentView()

@property UILabel* titleLabel;
@property UILabel* subtitleLabel;
@property UIImageView* background;
@property UIImageView* logo;
@property UIImageView* footerText;

@end

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
    [self initNavBar];
    [self initBackgroundImage];
    [self initLogo];
    [self initTitleLabel];
    [self initSubtitleLabel];
    [self initButton];
    [self initFooterText];
    [self initShadow];
}

-(void)initNavBar
{
    self.navBar = [[UINavigationBar alloc] init];
    
    if([self isIOS7OrLater]){
        self.navBar.tintColor = [UIColor colorWithRed:50.0/255 green:173.0/255 blue:95.0/255 alpha:1.0];
    }
    
    [self addSubview:self.navBar];
}

-(void)initBackgroundImage
{
    self.background = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"main-background"]];
    [self addSubview:self.background];
}

-(void)initLogo
{
    self.logo = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"logo"]];
    [self addSubview:self.logo];
}

-(void)initTitleLabel
{
    self.titleLabel = [[UILabel alloc] init];
    self.titleLabel.textColor = [UIColor whiteColor];
    self.titleLabel.text = @"Welcome to SupportKit";
    self.titleLabel.textAlignment = NSTextAlignmentCenter;
    self.titleLabel.font = [UIFont boldSystemFontOfSize:22];
    self.titleLabel.backgroundColor = [UIColor clearColor];
    
    [self addSubview:self.titleLabel];
}

-(void)initSubtitleLabel
{
    self.subtitleLabel = [[UILabel alloc] init];
    self.subtitleLabel.textColor = [UIColor whiteColor];
    self.subtitleLabel.text = @"You can invoke SupportKit from interactions made with your app, such as a button tap, or on specific events where help is required.";
    self.subtitleLabel.textAlignment = NSTextAlignmentCenter;
    self.subtitleLabel.font = [UIFont systemFontOfSize:15];
    self.subtitleLabel.numberOfLines = 0;
    self.subtitleLabel.backgroundColor = [UIColor clearColor];
    
    [self addSubview:self.subtitleLabel];
}

-(void)initButton
{
    self.button = [RPRoundedButton new];
    [self.button setTitle:@"Launch Help" forState:UIControlStateNormal];
    
    [self addSubview:self.button];
}

-(void)initFooterText
{
    self.footerText = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"text"]];
    [self addSubview:self.footerText];
}

-(void)initShadow
{
    self.layer.masksToBounds = NO;
    self.layer.shadowColor = [UIColor blackColor].CGColor;
    self.layer.shadowOffset = CGSizeMake(-2.0f, 0.0f);
    self.layer.shadowOpacity = 0.3f;
    self.layer.shadowRadius = 10.0f;
    self.layer.shadowPath = [UIBezierPath bezierPathWithRect:self.bounds].CGPath;
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    
    CGFloat navBarHeight = [self getNavBarHeight];
    self.navBar.frame = CGRectMake(0, 0, self.bounds.size.width, navBarHeight);
    
    // Scale the image to fit the width of the screen, but keep the aspect ratio
    float scale = self.frame.size.width / self.background.frame.size.width;
    int newHeight = ceil(self.background.frame.size.height * scale);
    self.background.frame = CGRectMake(0, navBarHeight, self.frame.size.width, newHeight);
    
    self.subtitleLabel.frame = CGRectMake(0, 0, MIN(self.bounds.size.width - 50, 320), 500);
    [self.subtitleLabel sizeToFit];
    self.subtitleLabel.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.center.y + 20);
    
    [self.titleLabel sizeToFit];
    self.titleLabel.center = CGPointMake(self.subtitleLabel.center.x, self.subtitleLabel.frame.origin.y - 5 - floor(self.titleLabel.frame.size.height / 2));
    
    self.logo.frame = CGRectMake(0, self.titleLabel.frame.origin.y - self.logo.frame.size.height - kLogoBottomPadding, self.logo.frame.size.width, self.logo.frame.size.height);
    self.logo.center = CGPointMake(self.titleLabel.center.x, self.logo.center.y);
    
    self.button.frame = CGRectMake(0,CGRectGetMaxY(self.subtitleLabel.frame) + 10, 200, 46);
    self.button.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.button.center.y);
    
    self.footerText.hidden = [self isLayoutPhoneInLandscape];
    self.footerText.frame = CGRectMake(0, CGRectGetMaxY(self.frame) - self.footerText.frame.size.height - kFooterTextBottomPadding, self.footerText.frame.size.width, self.footerText.frame.size.height);
    self.footerText.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.footerText.center.y);
}

-(CGFloat)getNavBarHeight
{
    int height = 44;
    
    if([self isLayoutPhoneInLandscape]){
        height = 32;
    }
    
    if([self isIOS7OrLater]){
        height += 20;
    }
    
    return height;
}

-(BOOL)isIOS7OrLater
{
    return floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_6_1;
}

-(BOOL)isLayoutPhoneInLandscape
{
    return UIDeviceOrientationIsLandscape([UIDevice currentDevice].orientation) && UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
}

@end
