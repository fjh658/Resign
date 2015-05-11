//
//  FileHandler.h
//  Resign
//
//  Created by Francesca Corsini on 12/04/15.
//  Copyright (c) 2015 Francesca Corsini. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import "YAProvisioningProfile.h"

typedef void(^SuccessBlock)(id);
typedef void(^ErrorBlock)(NSString*);
typedef void(^LogBlock)(NSString*);

static NSString *kKeyBundleIDChange = @"keyBundleIDChange";
static NSString *kCFBundleIdentifier = @"CFBundleIdentifier";
static NSString *kCFBundleDisplayName = @"CFBundleDisplayName";
static NSString *kCFBundleName = @"CFBundleName";
static NSString *kCFBundleShortVersionString = @"CFBundleShortVersionString";
static NSString *kCFBundleVersion = @"CFBundleVersion";
static NSString *kCFBundleIcons = @"CFBundleIcons";
static NSString *kCFBundlePrimaryIcon = @"CFBundlePrimaryIcon";
static NSString *kCFBundleIconFiles = @"CFBundleIconFiles";
static NSString *kCFBundleIconsipad = @"CFBundleIcons~ipad";
static NSString *kMinimumOSVersion = @"MinimumOSVersion";
static NSString *kPayloadDirName = @"Payload";
static NSString *kInfoPlistFilename = @"Info.plist";
static NSString *kEntitlementsPlistFilename = @"Entitlements.plist";
static NSString *kCodeSignatureDirectory = @"_CodeSignature";
static NSString *kMobileprovisionDirName = @"Library/MobileDevice/Provisioning Profiles";
static NSString *kMobileprovisionFilename = @"embedded.mobileprovision";
static NSString *kAppIdentifier = @"application-identifier";
static NSString *kTeamIdentifier = @"com.apple.developer.team-identifier";
static NSString *kKeychainAccessGroups = @"keychain-access-groups";

static NSString *kIconNormal = @"iconNormal";
static NSString *kIconRetina = @"iconRetina";


@interface FileHandler : NSObject <NSFileManagerDelegate>
{
    // blocks
	SuccessBlock successBlock;
	ErrorBlock errorBlock;
    LogBlock logBlock;
	
	// blocks
	SuccessBlock successResignBlock;
	ErrorBlock errorResignBlock;
	LogBlock logResignBlock;
	
    // date formatter
    NSDateFormatter *formatter;
    
    // global file manager
    NSFileManager *manager;
    
    // result of entitlements creation task
    NSString *entitlementsResult;
}

// array of provisioning profiles available
@property (nonatomic, strong) NSMutableArray *provisioningArray;

// index of the provisioning profile selected in the combo for the resign
@property (nonatomic) int provisioningIndex;

// bundle id selected for the resign
@property (nonatomic, strong) NSString *bundleId;

// display name selected for the resign
@property (nonatomic, strong) NSString *displayName;

// array of certificates available
@property (nonatomic, strong) NSMutableArray *certificatesArray;

// source ipa path
@property (nonatomic, strong) NSString *sourcePath;

// temp working directory
@property (nonatomic, strong) NSString *workingPath;

// path of the unzipped ipa (inside the workingPath)
@property (nonatomic, strong) NSString *appPath;

// destination ipa path
@property (nonatomic, strong) NSString *destinationPath;


+ (instancetype)sharedInstance;

+ (NSString*)getDocumentFolderPath;
- (BOOL)removeWorkingDirectory;
- (BOOL)removeCodeSignatureDirectory;

- (void)getDefaultBundleIDWithSuccess:(SuccessBlock)success error:(ErrorBlock)error;

- (void)getDefaultProductNameWithSuccess:(SuccessBlock)success error:(ErrorBlock)error;

- (void)getDefaultIconFilesWithSuccess:(SuccessBlock)success error:(ErrorBlock)error;

- (BOOL)searchForZipUtility;
- (void)unzipIpaFromSource:(NSString*)ipaFileName log:(LogBlock)log error:(ErrorBlock)error success:(SuccessBlock)success;
- (void)showIpaInfoWithSuccess:(SuccessBlock)success error:(ErrorBlock)error;
- (void)showProvisioningInfoWithSuccess:(SuccessBlock)success error:(ErrorBlock)error;
- (void)showCertificatesInfoWithSuccess:(SuccessBlock)success error:(ErrorBlock)error;

- (void)getProvisioningProfiles;
- (NSString*)getProvisioningInfoAtIndex:(NSInteger)index;

- (void)getCertificatesSuccess:(SuccessBlock)success error:(ErrorBlock)error;

- (void)resignFromProvisioning:(int)provisioningIndex bundleId:(NSString*)bundleId displayName:(NSString*)displayName log:(LogBlock)log error:(ErrorBlock)error success:(SuccessBlock)success;

@end