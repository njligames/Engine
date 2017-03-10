//
//  Shader.fsh
//  iOS
//
//  Created by James Folk on 2/28/17.
//  Copyright © 2017 James Folk. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
