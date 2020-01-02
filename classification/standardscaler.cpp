#include "standardscaler.h"

/*StandardScaler::StandardScaler(){
    setlocale(LC_NUMERIC, "en_US.UTF-8");
}*/

StandardScaler::StandardScaler(int numFeatures) : numFeatures(numFeatures) {
    featureMean = std::vector<float>(numFeatures, 0);
    featureStd = std::vector<float>(numFeatures, 0);

    setlocale(LC_NUMERIC, "en_US.UTF-8");
}

StandardScaler::StandardScaler(const char *filename){
    FILE* fid = fopen(filename, "r");
    char buf[1024];

    fgets(buf, 1024, fid);
    sscanf(buf, "%d\n", &numFeatures);

    featureMean = std::vector<float>(numFeatures, 0);
    featureStd = std::vector<float>(numFeatures, 0);
    for (int i = 0; i < numFeatures; i++){
        fgets(buf, 1024, fid);
        sscanf(buf, "%f,%f\n", &(featureMean[i]), &(featureStd[i]));
    }

    fclose(fid);
}

StandardScaler::~StandardScaler() {}

void StandardScaler::fit(cv::Mat data){
    std::vector<float> sum(numFeatures, 0);
    std::vector<float> squaredSum(numFeatures, 0);
    for (int i = 0; i < data.rows; i++){
        for (int j = 0; j < data.cols; j++){
            float val = data.at<float>(i, j);
            sum[j] += val;
            squaredSum[j] += (val * val);
        }
    }

    for (int j = 0; j < numFeatures; j++){
        featureMean[j] = (sum[j] / data.rows);
        featureStd[j] = (float)sqrt((squaredSum[j] / data.rows) - (featureMean[j] * featureMean[j]));
    }
}

void StandardScaler::transform(cv::Mat data){
    for (int i = 0; i < data.rows; i++){
        for (int j = 0; j < data.cols; j++){
            data.at<float>(i, j) = (data.at<float>(i, j) - featureMean[j]) / featureStd[j];
        }
    }
}

void StandardScaler::save(const char* filename){
    FILE* fid = fopen(filename, "w");

    fprintf(fid, "%d\n", numFeatures);
    for (int i = 0; i < numFeatures; i++) fprintf(fid, "%.5f,%.5f\n", featureMean[i], featureStd[i]);

    fclose(fid);
}
/*
void StandardScaler::load(const char* filename){
    FILE* fid = fopen(filename, "r");
    char buf[1024];

    fgets(buf, 1024, fid);
    int* numF;
    sscanf(buf, "%d\n", numF);
    numFeatures = *numF;
    *featureMean = std::vector<float>(numFeatures, 0);
    *featureStd = std::vector<float>(numFeatures, 0);

    float* fMean;
    float* fStd;
    for (int i = 0; i < numFeatures; i++){
        fgets(buf, 1024, fid);
        sscanf(buf, "%f,%f\n", fMean, fStd);
        (*featureMean)[i] = *fMean;
        (*featureStd)[i] = *fStd;
    }

    fclose(fid);
}*/
