//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// group.cpp
//
// Identification: src/optimizer/group.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "optimizer/group.h"

namespace peloton {
namespace optimizer {

//===--------------------------------------------------------------------===//
// Group
//===--------------------------------------------------------------------===//
Group::Group(GroupID id) : id_(id) {}
void Group::add_item(Operator op) {
  // TODO(abpoms): do duplicate checking
  items_.push_back(op);
}
void Group::AddExpression(std::shared_ptr<GroupExpression> expr) {
  // Do duplicate detection
  expr->SetGroupID(id_);
  expressions_.push_back(expr);
}

void Group::SetExpressionCost(std::shared_ptr<GroupExpression> expr,
                              double cost, PropertySet properties) {
  auto it = lowest_cost_expressions_.find(properties);
  if (it == lowest_cost_expressions_.end()) {
    // No other cost to compare against
    lowest_cost_expressions_.insert(
        std::make_pair(properties, std::make_tuple(cost, expr)));
  } else {
    // Only insert if the cost is lower than the existing cost
    if (std::get<0>(it->second) > cost) {
      lowest_cost_expressions_[properties] = std::make_tuple(cost, expr);
    }
  }
}

std::shared_ptr<GroupExpression> Group::GetBestExpression(
    PropertySet properties) {
  auto it = lowest_cost_expressions_.find(properties);
  if (it != lowest_cost_expressions_.end()) {
    return std::get<1>(it->second);
  }
  return nullptr;
}

const std::vector<std::shared_ptr<GroupExpression>> &Group::GetExpressions()
    const {
  return expressions_;
}

} /* namespace optimizer */
} /* namespace peloton */
