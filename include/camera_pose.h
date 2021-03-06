//
// Created by Tomas Krejci on 6/6/16.
//

#ifndef TONAV_CAMERA_POSE_H
#define TONAV_CAMERA_POSE_H

#include <Eigen/Dense>
#include <limits>
#include <set>
#include <memory>

class BodyState;
class Filter;

class CameraPose {
public:
    //CameraPose() = default;
    //CameraPose(const CameraPose& other) = default;
    CameraPose(const BodyState& body_state);
    
    //CameraPose& operator=(const CameraPose& other) = default;

    std::size_t getActiveFeaturesCount() const;
    void setActiveFeaturesCount(std::size_t i);
    void decreaseActiveFeaturesCount(int feature_id);
    
    BodyState& getBodyState();
    const BodyState& getBodyState() const;

    /**
     * @brief Time of body state
     */
    double time() const;
    
    /** @brief Get orientation \f$ {}^G \mathbf{q}_B \f$ of this camera frame in global frame. */
    const Eigen::Quaterniond& getBodyOrientationInGlobalFrame() const;
    
    /** @brief Get orientation \f$ {}^G \mathbf{q}_C \f$ of this camera frame in global frame. */
    Eigen::Quaterniond getCameraOrientationInGlobalFrame(const Filter& filter) const;
    
    /** @brief Get position \f$ {}^G \mathbf{p}_B \f$ of this camera frame in global frame. */
    const Eigen::Vector3d& getBodyPositionInGlobalFrame() const;
    
    /** @brief Get position \f$ {}^G \mathbf{p}_C \f$ of this camera frame in global frame. */
    Eigen::Vector3d getCameraPositionInGlobalFrame(const Filter& filter) const;
    
    /** @brief Get velocity \f$ {}^G\mathbf{v}_B \f$ of this camera frame in global frame. */
    const Eigen::Vector3d& getBodyVelocityInGlobalFrame() const;
    
    Eigen::Quaterniond getRotationToOtherPose(const CameraPose& other, const Filter& filter) const;
    
    Eigen::Vector3d getPositionOfAnotherPose(const CameraPose& other, const Filter& filter) const;

    void rememberFeatureId(int feature_id);

private:
    std::set<int> feature_ids_;
    std::shared_ptr<BodyState> body_state_;
    std::size_t features_active_;
};

#endif //TONAV_CAMERA_POSE_H
