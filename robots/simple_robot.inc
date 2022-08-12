define laser ranger(
    sensor(
        range [ 0.0 5.6 ]
        fov 240.0
        samples 240
    )
    
    color "blue"
    size [ 0.05 0.1 0.05 ]
    
    block( points 4
        point[0] [0 0]
        point[1] [0 1]
        point[2] [1 1]
        point[3] [1 0]
        z [0 1]
    )
)

define simple_robot position(
    odom_error [0.03 0.03 0.00 0.05]
    localization "odom"
    size [ 0.5 0.5 0.5 ]
    
    block( points 8
        point[0] [0 0]
        point[1] [0.707 0.707]
        point[2] [1.707 0.707]
        point[3] [2.414 0]
        point[4] [2.414 -1]
        point[5] [1.707 -1.707]
        point[6] [0.707 -1.707]
        point[7] [0 -1]
        z [0 1]
    )
    
    gui_nose 1
    drive "diff"
    color "red"
    
    laser(pose [0.27. 0.0 -0.4 0.0])
    laser(pose [0.191 0.191 -0.4 45.0])
    laser(pose [0.191 -0.191 -0.4 315.0])
)
