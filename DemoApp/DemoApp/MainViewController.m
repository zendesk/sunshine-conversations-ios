//
//  MainViewController.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/10/13.
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import "MainViewController.h"
#import "MainContentView.h"
#import <Smooch/Smooch.h>

@interface MainViewController ()

@property NSString* initialURL;
@property MainContentView* contentView;

@end

@implementation MainViewController

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self initContentView];
}

-(void)initContentView
{
    self.contentView = [[MainContentView alloc] initWithFrame:self.view.bounds];
    
    UINavigationItem* navItem = [[UINavigationItem alloc] initWithTitle:@""];
    navItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Speak to us" style:UIBarButtonItemStylePlain target:self action:@selector(launch)];
    [self.contentView.navBar pushNavigationItem:navItem animated:NO];
    
    [self.contentView.button addTarget:self action:@selector(launch) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview:self.contentView];
}

-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    self.contentView.frame = self.view.bounds;
}

-(void)launch
{
    [Smooch show];
}

@end
