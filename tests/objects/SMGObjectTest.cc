/*
 * SMGObjectTest.cc
 *
 *  Created on: Dec 3, 2015
 *      Author: pmuller
 */

/*
 *  This file is part of SMG, a symbolic memory graph Java library
 *  Originally developed as part of CPAChecker, the configurable software verification platform
 *
 *  Copyright (C) 2011-2015  Petr Muller
 *  Copyright (C) 2007-2014  Dirk Beyer
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include <gtest/gtest.h>
#include "objects/SMGObject.hh"

namespace smg {

static int SIZE8 = 8;
static int SIZE12 = 12;

class TestingObject : public SMGObject {
 public:
  TestingObject(const int size, const std::string label) : SMGObject(size, label) {}
  ~TestingObject() {};
  TestingObject(const TestingObject&) = default;

  virtual bool NotNull() const { return true; }
  virtual bool IsAbstract() const override { return false; }
  void Accept(SMGObjectVisitor& visitor) const override { (void)visitor; }
  virtual bool IsMoreGeneral(const SMGObject&) const override {
    return false;
  };
  virtual const SMGObject& Join(const SMGObject&) const override { return *this; }
};

TestingObject object_8 = TestingObject(8, "label");
TestingObject object_12 = TestingObject(12, "another label");

TEST(SMGObject, GetNullObjectTest) {
  const SMGObject& null_object = SMGObject::GetNullObject();
  EXPECT_FALSE(null_object.NotNull());
  EXPECT_TRUE(object_8.NotNull());
  EXPECT_FALSE(null_object.IsAbstract());
  EXPECT_FALSE(null_object.IsMoreGeneral(object_8));
  EXPECT_FALSE(null_object.IsMoreGeneral(null_object));
  EXPECT_EQ(&null_object, &null_object.Join(null_object));
  EXPECT_EQ(&object_8, &null_object.Join(object_8));
}

//	public final void testSMGObjectIntString() {
//    Assert.assertEquals(SIZE8, object8.getSize());
//    Assert.assertEquals("label", object8.getLabel());
//    Assert.assertEquals(SIZE12, object12.getSize());
//    Assert.assertEquals("another label", object12.getLabel());
//    SMGObject object12copy = new TestingObject(object12);
//    Assert.assertEquals(SIZE12, object12copy.getSize());
//    Assert.assertEquals("another label", object12copy.getLabel());
//  }

TEST(SMGObject, PropertySanity) {
  EXPECT_EQ(SIZE8, object_8.GetSize());
  EXPECT_STREQ("label", object_8.GetLabel().c_str());
  EXPECT_EQ(SIZE12, object_12.GetSize());
  EXPECT_STREQ("another label", object_12.GetLabel().c_str());
  SMGObject* object_12_copy = new TestingObject(object_12);
  EXPECT_EQ(SIZE12, object_12_copy->GetSize());
  EXPECT_STREQ("another label", object_12_copy->GetLabel().c_str());
  delete object_12_copy;
}

//  private static class TestingObject extends SMGObject {
//
//    protected TestingObject(final int pSize, final String pLabel) {
//      super(pSize, pLabel);
//    }
//
//    protected TestingObject(final TestingObject pOther) {
//      super(pOther);
//    }
//
//    @Override
//    public boolean isAbstract() {
//      return false;
//    }
//
//    @Override
//    public void accept(final SMGObjectVisitor pVisitor) {
//      pVisitor.visit(this);
//    }
//
//    @Override
//    public boolean isMoreGeneral(final SMGObject pOther) {
//      return false;
//    }
//
//    @Override
//    public SMGObject join(final SMGObject pOther) {
//      return pOther;
//    }
//  }
//
//  @Test
//	public final void testVisitorOnNull() {
//    SMGObject nullObject = SMGObject.getNullObject();
//    SMGObjectVisitor visitor = new SMGObjectVisitor() {
//      @Override
//      public void visit(final SMGObject pObject) {
//        Assert.assertFalse(pObject.notNull());
//      }
//    };
//    nullObject.accept(visitor);
//  }
//}

}  // namespace smg
