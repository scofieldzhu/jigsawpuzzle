#ifndef __gameconfig_h__
#define __gameconfig_h__

class GameConfig
{
public:
    QPixmap originimage;
    int gridrows;
    int gridcols;
    int watchimageseconds;
    
    GameConfig();
    ~GameConfig();
};

#endif
