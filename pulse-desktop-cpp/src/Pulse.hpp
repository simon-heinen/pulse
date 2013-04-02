#ifndef PULSE_HPP
#define	PULSE_HPP

#include <string>
#include <vector>
#include <opencv2/objdetect/objdetect.hpp>
#include "EvmGdownIIR.hpp"

using std::string;
using std::vector;
using cv::Mat;
using cv::Mat1d;
using cv::Rect;
using cv::Size;
using cv::CascadeClassifier;

class Pulse {
public:
    Pulse();
    virtual ~Pulse();
    
    void load(const string& filename);
    void start(int width, int height);
    void onFrame(Mat& frame);

    double relativeMinFaceSize;
    double fps;
    bool magnify;

    struct Face {
        int id;
        int deleteIn;
        bool selected;
        EvmGdownIIR evm;
        Mat evmMat;
        Size evmSize;
        Rect evmBox;
        Rect box;
        Rect roi;
        Mat1d timestamps;
        Mat1d raw;
        Mat1d pulse;
        Mat1d bpms;
        double bpm;
        
        cv::Mat1i maxIdx;

        Face(int id, const Rect& box, int deleteIn);
        virtual ~Face();
        int nearestBox(const vector<Rect>& boxes);
        void updateBox(const Rect& box);
    };
    
private:
    void onFace(Mat& frame, Face& face, const Rect& box);
    void peakDetection(Face& face);
    void calculateBpm(Face& face);
    int nearestFace(const Rect& box);
    
    uint64 t;
    Size minFaceSize;
    CascadeClassifier classifier;
    Mat gray;
    vector<Rect> boxes;
    Mat1d powerSpectrum;
    vector<Face> faces;
    int nextFaceId;
    int deleteFaceIn;


};

#endif	/* PULSE_HPP */

