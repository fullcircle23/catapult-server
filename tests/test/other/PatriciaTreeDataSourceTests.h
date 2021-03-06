/**
*** Copyright (c) 2016-present,
*** Jaguar0625, gimre, BloodyRookie, Tech Bureau, Corp. All rights reserved.
***
*** This file is part of Catapult.
***
*** Catapult is free software: you can redistribute it and/or modify
*** it under the terms of the GNU Lesser General Public License as published by
*** the Free Software Foundation, either version 3 of the License, or
*** (at your option) any later version.
***
*** Catapult is distributed in the hope that it will be useful,
*** but WITHOUT ANY WARRANTY; without even the implied warranty of
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*** GNU Lesser General Public License for more details.
***
*** You should have received a copy of the GNU Lesser General Public License
*** along with Catapult. If not, see <http://www.gnu.org/licenses/>.
**/

#pragma once
#include "catapult/tree/TreeNode.h"
#include "tests/TestHarness.h"

namespace catapult { namespace test {

	/// Patricia tree data source test suite.
	template<typename TTraits>
	class PatriciaTreeDataSourceTests {
	private:
		using DataSourceType = typename TTraits::DataSourceType;

	public:
		// region constructor

		static void AssertDataSourceIsInitiallyEmpty() {
			// Act:
			DataSourceType dataSource;

			// Assert:
			EXPECT_EQ(0u, dataSource.size());
		}

		// endregion

		// region set

		static void AssertCanSetLeafTreeNode() {
			// Arrange:
			DataSourceType dataSource;

			// Act:
			auto node = tree::LeafTreeNode(tree::TreeNodePath(0x64'6F'67'00), GenerateRandomData<Hash256_Size>());
			dataSource.set(node);

			// Assert:
			EXPECT_EQ(1u, dataSource.size());
		}

		static void AssertCanSetBranchTreeNode() {
			// Arrange:
			DataSourceType dataSource;

			// Act:
			auto node = tree::BranchTreeNode(tree::TreeNodePath(0x64'6F'67'00));
			dataSource.set(node);

			// Assert:
			EXPECT_EQ(1u, dataSource.size());
		}

		// endregion

		// region get

		static void AssertCannotGetUnknownNode() {
			// Arrange:
			auto node = tree::LeafTreeNode(tree::TreeNodePath(0x64'6F'67'00), GenerateRandomData<Hash256_Size>());

			DataSourceType dataSource;
			dataSource.set(node);

			// Act:
			auto pDataSourceNode = dataSource.get(GenerateRandomData<Hash256_Size>());

			// Assert:
			EXPECT_FALSE(!!pDataSourceNode);
		}

		static void AssertCanGetLeafNode() {
			// Arrange:
			auto node = tree::LeafTreeNode(tree::TreeNodePath(0x64'6F'67'00), GenerateRandomData<Hash256_Size>());

			DataSourceType dataSource;
			dataSource.set(node);

			// Act:
			auto pDataSourceNode = dataSource.get(node.hash());

			// Assert:
			ASSERT_TRUE(!!pDataSourceNode);
			EXPECT_TRUE(pDataSourceNode->isLeaf());
			EXPECT_EQ(node.hash(), pDataSourceNode->hash());
		}

		static void AssertCanGetBranchNode() {
			// Arrange:
			auto node = tree::BranchTreeNode(tree::TreeNodePath(0x64'6F'67'00));

			DataSourceType dataSource;
			dataSource.set(node);

			// Act:
			auto pDataSourceNode = dataSource.get(node.hash());

			// Assert:
			ASSERT_TRUE(!!pDataSourceNode);
			EXPECT_TRUE(pDataSourceNode->isBranch());
			EXPECT_EQ(node.hash(), pDataSourceNode->hash());
		}

		// endregion

	};

#define MAKE_PATRICIA_TREE_DATA_SOURCE_TEST(TRAITS_NAME, TEST_NAME) \
	TEST(TEST_CLASS, TEST_NAME) { test::PatriciaTreeDataSourceTests<TRAITS_NAME>::Assert##TEST_NAME(); }

#define DEFINE_PATRICIA_TREE_DATA_SOURCE_TESTS(TRAITS_NAME) \
	MAKE_PATRICIA_TREE_DATA_SOURCE_TEST(TRAITS_NAME, DataSourceIsInitiallyEmpty) \
	\
	MAKE_PATRICIA_TREE_DATA_SOURCE_TEST(TRAITS_NAME, CanSetLeafTreeNode) \
	MAKE_PATRICIA_TREE_DATA_SOURCE_TEST(TRAITS_NAME, CanSetBranchTreeNode) \
	\
	MAKE_PATRICIA_TREE_DATA_SOURCE_TEST(TRAITS_NAME, CannotGetUnknownNode) \
	MAKE_PATRICIA_TREE_DATA_SOURCE_TEST(TRAITS_NAME, CanGetLeafNode) \
	MAKE_PATRICIA_TREE_DATA_SOURCE_TEST(TRAITS_NAME, CanGetBranchNode)
}}
