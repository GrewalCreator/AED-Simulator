#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

class AED;

class MediaPlayer
{
public:
    MediaPlayer(AED& aed);

private:
    AED* automatedED;
};

#endif // MEDIAPLAYER_H
