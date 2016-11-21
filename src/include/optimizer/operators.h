
//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// operators.h
//
// Identification: src/include/optimizer/operators.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include "optimizer/column.h"
#include "optimizer/group.h"
#include "optimizer/operator_node.h"
#include "optimizer/query_operators.h"
#include "optimizer/util.h"

#include <vector>

namespace peloton {

namespace expression {
class AbstractExpression;
}

namespace optimizer {

//===--------------------------------------------------------------------===//
// Leaf
//===--------------------------------------------------------------------===//
class LeafOperator : OperatorNode<LeafOperator> {
 public:
  static Operator make(GroupID group);

  GroupID origin_group;
};

//===--------------------------------------------------------------------===//
// Get
//===--------------------------------------------------------------------===//
class LogicalGet : public OperatorNode<LogicalGet> {
 public:
  static Operator make(storage::DataTable *table);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  storage::DataTable *table;
};

//===--------------------------------------------------------------------===//
// Project
//===--------------------------------------------------------------------===//
class LogicalProject : public OperatorNode<LogicalProject> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// Select
//===--------------------------------------------------------------------===//
class LogicalFilter : public OperatorNode<LogicalFilter> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// InnerJoin
//===--------------------------------------------------------------------===//
class LogicalInnerJoin : public OperatorNode<LogicalInnerJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// LeftJoin
//===--------------------------------------------------------------------===//
class LogicalLeftJoin : public OperatorNode<LogicalLeftJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// RightJoin
//===--------------------------------------------------------------------===//
class LogicalRightJoin : public OperatorNode<LogicalRightJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// OuterJoin
//===--------------------------------------------------------------------===//
class LogicalOuterJoin : public OperatorNode<LogicalOuterJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// Aggregate
//===--------------------------------------------------------------------===//
class LogicalAggregate : public OperatorNode<LogicalAggregate> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// Limit
//===--------------------------------------------------------------------===//
class LogicalLimit : public OperatorNode<LogicalLimit> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// Scan
//===--------------------------------------------------------------------===//
class PhysicalScan : public OperatorNode<PhysicalScan> {
 public:
  static Operator make(storage::DataTable *table, std::vector<Column *> cols);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  storage::DataTable *table;
  std::vector<Column *> columns;
};

//===--------------------------------------------------------------------===//
// ComputeExprs
//===--------------------------------------------------------------------===//
class PhysicalComputeExprs : public OperatorNode<PhysicalComputeExprs> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// Filter
//===--------------------------------------------------------------------===//
class PhysicalFilter : public OperatorNode<PhysicalFilter> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// InnerNLJoin
//===--------------------------------------------------------------------===//
class PhysicalInnerNLJoin : public OperatorNode<PhysicalInnerNLJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// LeftNLJoin
//===--------------------------------------------------------------------===//
class PhysicalLeftNLJoin : public OperatorNode<PhysicalLeftNLJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// RightNLJoin
//===--------------------------------------------------------------------===//
class PhysicalRightNLJoin : public OperatorNode<PhysicalRightNLJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// OuterNLJoin
//===--------------------------------------------------------------------===//
class PhysicalOuterNLJoin : public OperatorNode<PhysicalOuterNLJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// InnerHashJoin
//===--------------------------------------------------------------------===//
class PhysicalInnerHashJoin : public OperatorNode<PhysicalInnerHashJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// LeftHashJoin
//===--------------------------------------------------------------------===//
class PhysicalLeftHashJoin : public OperatorNode<PhysicalLeftHashJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// RightHashJoin
//===--------------------------------------------------------------------===//
class PhysicalRightHashJoin : public OperatorNode<PhysicalRightHashJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// OuterHashJoin
//===--------------------------------------------------------------------===//
class PhysicalOuterHashJoin : public OperatorNode<PhysicalOuterHashJoin> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// QueryExpression (predicate/select_list)
//===--------------------------------------------------------------------===//
class QueryExpressionOperator : public OperatorNode<QueryExpressionOperator> {
 public:
  static Operator make(expression::AbstractExpression *expression);

  std::unique_ptr<expression::AbstractExpression> expression_;
};

//===--------------------------------------------------------------------===//
// Variable
//===--------------------------------------------------------------------===//
class ExprVariable : public OperatorNode<ExprVariable> {
 public:
  static Operator make(Column *column);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  Column *column;
};

//===--------------------------------------------------------------------===//
// Constant
//===--------------------------------------------------------------------===//
class ExprConstant : public OperatorNode<ExprConstant> {
  ~ExprConstant() {}

 public:
  static Operator make(const common::Value value);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  common::Value value;
};

//===--------------------------------------------------------------------===//
// Compare
//===--------------------------------------------------------------------===//
class ExprCompare : public OperatorNode<ExprCompare> {
 public:
  static Operator make(ExpressionType type);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  ExpressionType expr_type;
};

//===--------------------------------------------------------------------===//
// Boolean Operation
//===--------------------------------------------------------------------===//
enum class BoolOpType {
  Not,
  And,
  Or,
};

class ExprBoolOp : public OperatorNode<ExprBoolOp> {
 public:
  static Operator make(BoolOpType type);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  BoolOpType bool_type_;
};

//===--------------------------------------------------------------------===//
// Operation (e.g. +, -, string functions)
//===--------------------------------------------------------------------===//
class ExprOp : public OperatorNode<ExprOp> {
 public:
  static Operator make(ExpressionType type, common::Type::TypeId return_type);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  ExpressionType expr_type_;
  common::Type::TypeId return_type_;
};

//===--------------------------------------------------------------------===//
// ProjectList
//===--------------------------------------------------------------------===//
class ExprProjectList : public OperatorNode<ExprProjectList> {
 public:
  static Operator make();
};

//===--------------------------------------------------------------------===//
// ProjectColumn
//===--------------------------------------------------------------------===//
class ExprProjectColumn : public OperatorNode<ExprProjectColumn> {
 public:
  static Operator make(Column *column);

  bool operator==(const BaseOperatorNode &r) override;

  hash_t Hash() const override;

  Column *column_;
};

} /* namespace optimizer */
} /* namespace peloton */
