/*
Outlier removal class
Provide a set of outlier removal methods
along with interface to robustPGO
author: Yun Chang
*/

#ifndef OUTLIERREMOVAL_H
#define OUTLIERREMOVAL_H

namespace RobustPGO {

class OutlierRemoval {
public:
	virtual ~OutlierRemoval() = default;

	/*! \brief Process new measurements and reject outliers
   *  process the new measurements and update the "good set" of measurements
   *  - new_factors: factors from the new measurements
   *  - new_values: linearization point of the new measurements
   *	- nfg: the factors after processing new measurements and outlier removal
   * 	- values: the values after processing new measurements and outlier removal
   *  - returns: boolean of if optimization should be called or not
   */
	virtual bool removeOutliers(const gtsam::NonlinearFactorGraph& new_factors,
				               const gtsam::Values& new_values,
				               gtsam::NonlinearFactorGraph& nfg,
				               gtsam::Values& values) = 0;

	/*! \brief Process new measurements while bypassing reject outliers
   *  add the new measurements and assume all the new measurements are inliers
   *  - new_factors: factors from the new measurements
   *  - new_values: linearization point of the new measurements
   *	- nfg: the factors after adding new measurements
   * 	- values: the values after adding  new measurements
   *  - returns: boolean of if optimization should be called or not
   */
	virtual bool addMeasurements(
			const gtsam::NonlinearFactorGraph& new_factors,
			const gtsam::Values& new_values,
			gtsam::NonlinearFactorGraph& nfg,
			gtsam::Values& values) = 0; // force a loop closure

	/*! \brief Save any data in the outlier removal process
   *  - folder_path: path to directory to save results in
   */
	virtual void saveData(std::string folder_path) {}

	void setQuiet() { debug_ = false; }

protected:
	bool debug_ = true;
};

}
#endif
