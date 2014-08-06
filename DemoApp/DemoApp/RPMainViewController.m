//
//  RPSideMenuViewController.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/10/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPMainViewController.h"
#import "RPMainContentView.h"
#import "RPZendeskPickerView.h"
#import <SupportKit/SupportKit.h>

@interface RPMainViewController ()

@property NSString* initialURL;
@property RPMainContentView* contentView;
@property RPZendeskPickerView* pickerView;
@property BOOL showingSidePanel;

@end

@implementation RPMainViewController

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.showingSidePanel = NO;
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self initPickerView];
    [self initContentView];
    [self initGestureRecognizers];
}

-(void)initContentView
{
    self.contentView = [[RPMainContentView alloc] initWithFrame:[self getContentViewFrame]];
    
    UINavigationItem* navItem = [[UINavigationItem alloc] initWithTitle:@""];
    navItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Options" style:UIBarButtonItemStylePlain target:self action:@selector(showMenu)];
    navItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Help" style:UIBarButtonItemStylePlain target:self action:@selector(launch)];
    [self.contentView.navBar pushNavigationItem:navItem animated:NO];
    
    [self.contentView.button addTarget:self action:@selector(launch) forControlEvents:UIControlEventTouchUpInside];
    [self.contentView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hideMenu)]];
    
    [self.view addSubview:self.contentView];
}

-(void)initPickerView
{
    self.pickerView = [[RPZendeskPickerView alloc] initWithFrame:[self getPickerViewFrame]];
    self.pickerView.hidden = YES;
    self.pickerView.backgroundColor =  [UIColor colorWithRed:50.0/255 green:173.0/255 blue:95.0/255 alpha:1.0];
    
    [self.view addSubview:self.pickerView];
    
    [self.pickerView.launchButton addTarget:self action:@selector(launch) forControlEvents:UIControlEventTouchUpInside];
    [self.pickerView.showGestureHintButton addTarget:self action:@selector(launchHint) forControlEvents:UIControlEventTouchUpInside];
}

-(void)initGestureRecognizers
{
    UISwipeGestureRecognizer* swipeLeft = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(hideMenu)];
    swipeLeft.direction = UISwipeGestureRecognizerDirectionLeft;
    [self.view addGestureRecognizer:swipeLeft];
    
    UISwipeGestureRecognizer* swipeRight = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(showMenu)];
    swipeRight.direction = UISwipeGestureRecognizerDirectionRight;
    [self.view addGestureRecognizer:swipeRight];
}

-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    self.contentView.frame = [self getContentViewFrame];
    self.pickerView.frame = [self getPickerViewFrame];
}

-(void)launch
{
    [self reinitializeSettings];
    [SupportKit show];
}

-(void)launchHint
{
    [self reinitializeSettings];
    [SupportKit showWithGestureHint];
}

-(void)reinitializeSettings
{
    SKTSettings* settings = [[SKTSettings alloc] init];
    settings.knowledgeBaseURL = self.pickerView.textField.text;
    
    // WARNING: Do not call +initWithSettings: more than once in your app.
    // We need to call it every time here to change the knowledge base URL based on the text field; your URL should be hardcoded.
    [SupportKit initWithSettings:settings];
}

-(void)showMenu
{
    self.showingSidePanel = YES;
    self.pickerView.hidden = NO;
    
    [UIView animateWithDuration:0.25 animations:^{
        self.contentView.frame = [self getContentViewFrame];
        self.pickerView.frame = [self getPickerViewFrame];
    }];
}

-(void)hideMenu
{
    self.showingSidePanel = NO;
    
    // Hide the keyboard
    [self.pickerView.textField resignFirstResponder];
    
    [UIView animateWithDuration:0.25 animations:^{
        self.contentView.frame = [self getContentViewFrame];
        self.pickerView.frame = [self getPickerViewFrame];
    } completion:^(BOOL finished) {
        self.pickerView.hidden = YES;
    }];
}

-(CGRect)getPickerViewFrame
{
    CGRect frame = CGRectMake(0, 0, floor(self.view.bounds.size.width * 0.85), self.view.bounds.size.height);
    if(!self.showingSidePanel){
        frame = CGRectOffset(frame, -floor(self.view.bounds.size.width * 0.85), 0);
    }
    return frame;
}

-(CGRect)getContentViewFrame
{
    CGRect frame = self.view.bounds;
    if(self.showingSidePanel){
        frame = CGRectOffset(frame, floor(self.view.bounds.size.width * 0.85), 0);
    }
    return frame;
}

@end
