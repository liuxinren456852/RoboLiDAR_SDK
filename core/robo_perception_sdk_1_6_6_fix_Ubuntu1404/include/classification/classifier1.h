/**
 *****************************************************************************
 * COPYRIGHT STATEMENT
 * Copyright (c) 2018, Robosense Co.,Ltd. - www.robosense.ai
 * All Rights Reserved.
 *
 * You can not use, copy or spread without official authorization.
 *****************************************************************************
 *
 * Author: Robosense Perception Group
 * Version: 2.0
 * Date: 2017.12
 *
 * DESCRIPTION
 *
 * Robosense classification module, for object recognition.
 *
 */

#ifndef CLASSIFIER_1_H
#define CLASSIFIER_1_H

#include "common/data_type/robo_types.h"
#include "classification/c_api.h"
#include "classification/classifyCommon.h"

namespace Robosense{
/**
 * @brief The Classifier Class with Method 1.
 * @ingroup postprocessing
 */
class Classifier1{

  public:

  /**
   * @brief Construct a classifier with Method 2
   * @param[in] lidar_config: configure parameter by user
   * @param[in] with_enhance: use enhance or not, the enhanced procedure is a refine post-process.
   */
  Classifier1(bool with_enhance = true);
  ~Classifier1();

  /**
 * @brief load the train modelfile.
 * @param[in] modelfile: the model path.
 */
  void loadModel(std::string modelFile);


  /**
   * @brief label the input trackers, the multi-classifier is of 5 classes
   * 0:represents background, 1:represents pedestrian, 2:represents bicycle/bike, 3:represents car, 4:represents truck/bus
   * @param[in,out] tlabels: vector of perception targets with track information
   */
  void classifierAPI(std::vector<NormalRoboPerceptron>& tlabels);


  /**
   * @brief label the input target, the multi-classifier is of 5 classes
   * @param in_target: input target with perception information
   */
  void classifierAPI2(NormalRoboPerceptron& in_target);

  /**
   * @brief refresh lidar height parameters, should be called for every frame
   * @param estimate_lidar_height
   */
  void freshLidarHeight(const float &estimate_lidar_height);

  private:
  std::vector<float> getProbabilities(std::vector<float> &log_probabilities);
  int objectClassify(const NormalRoboCluster &cluster,std::vector<float> &outProbability);
  int getLabelFromProb(const std::vector<float> &inProbVec);

  bool with_enhance_;
  bool model_flag_;

  BoosterHandle  h_booster_;

  ClassifyUtil<NormalPoint> *classify_util_;

  float estimate_lidar_height_;


};

}

#endif
