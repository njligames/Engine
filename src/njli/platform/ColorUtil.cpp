//
//  ColorUtil.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 4/24/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#include "ColorUtil.h"



 const btMatrix3x3 njli::ColorUtil::RGB_TO_YIQ = btMatrix3x3(0.299,  0.587,  0.144,
                                                             0.596, -0.274, -0.321,
                                                             0.211, -0.523,  0.311);


 const btMatrix3x3 njli::ColorUtil::YIQ_TO_RGB = btMatrix3x3(1.000,  0.956,  0.621,
                                                             1.000, -0.272, -0.647,
                                                             1.000, -1.107,  1.705);
