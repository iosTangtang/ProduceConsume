//
//  NSMutableArray+Queue.h
//  ProducerConsumerOC
//
//  Created by Tangtang on 2016/10/13.
//  Copyright © 2016年 Tangtang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (Queue)

- (void)pcr_enterQueue:(NSString *)str;

- (BOOL)pcr_delQueue;

@end
