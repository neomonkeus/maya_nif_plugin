// Maya NIF File Translator Plugin
// Based on information from NIFLA

/* Copyright (c) 2005, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.

   * Neither the name of the NIF File Format Library and Tools
     project nor the names of its contributors may be used to endorse
     or promote products derived from this software without specific
     prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE. */

#ifndef NIF_PLUGIN_H
#define NIF_PLUGIN_H

//--Includes--//
#include <maya/MDagPath.h>
#include <maya/MEulerRotation.h>
#include <maya/MFloatArray.h>
#include <maya/MFnBase.h>
#include <maya/MFnComponent.h>
#include <maya/MFnData.h>
#include <maya/MFnDagNode.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnIkJoint.h>
#include <maya/MFnMatrixData.h>
#include <maya/MFnMesh.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnPhongShader.h>
#include <maya/MFnPlugin.h>
#include <maya/MFnSet.h>
#include <maya/MFnTransform.h>
#include <maya/MFStream.h>
#include <maya/MGlobal.h>
#include <maya/MIntArray.h>
#include <maya/MIOStream.h> 
#include <maya/MItDag.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MItGeometry.h>
#include <maya/MItSelectionList.h>
#include <maya/MMatrix.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MPointArray.h>
#include <maya/MPxFileTranslator.h>
#include <maya/MQuaternion.h>
#include <maya/MSelectionList.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MFnSkinCluster.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MVector.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MItMeshPolygon.h>

#include <string.h> 
#include <vector>
#include <cmath>

#include "niflib.h"

//--NifTranslator Class--//

//This class implements the file translation functionality of the plug-in
class NifTranslator : public MPxFileTranslator {
public:
	//Constructor
	NifTranslator () {};

	//Destructor
	virtual ~NifTranslator () {};

	//Factory function for Maya to use to create a NifTranslator
	static void* creator() { return new NifTranslator(); }

	//This routine is called by Maya when it is necessary to load a file of a type supported by this translator.
	//Responsible for reading the contents of the given file, and creating Maya objects via API or MEL calls to reflect the data in the file.
	MStatus reader (const MFileObject& file, const MString& optionsString, MPxFileTranslator::FileAccessMode mode);
	
	//This routine is called by Maya when it is necessary to save a file of a type supported by this translator.
	//Responsible for traversing all objects in the current Maya scene, and writing a representation to the given file in the supported format.
	MStatus writer (const MFileObject& file, const MString& optionsString, MPxFileTranslator::FileAccessMode mode);
	
	//Returns true if the class has a read method and false otherwise
	bool haveReadMethod () const { return true; }

	//Returns true if the class has a reference method and false otherwise
	bool haveReferenceMethod () const { return false; }

	//Returns true if the class has a write method and false otherwise
	bool haveWriteMethod () const { return true; }

	//Returns true if the class can deal with namespaces and false otherwise
	bool haveNamespaceSupport () const { return false; }

	//Returns a string containing the default extension of the translator, excluding the period at the beginning
	MString defaultExtension () const { return MString("nif"); }

	//Returns true if the class can open and import files
	//Returns false if the class can only import files
	bool canBeOpened() const { return true; }

	// This routine must use passed data to determine if the file is of a type supported by this translator
	MFileKind identifyFile (const MFileObject& fileName, const char* buffer, short size) const;

private:
	void ImportNodes( blk_ref block, map< blk_ref, MDagPath > & objs, MObject parent = MObject::kNullObj );
	MDagPath ImportMesh( blk_ref block, MObject parent = MObject::kNullObj );
	MObject ImportMaterial( blk_ref block );
	MObject ImportTexture( blk_ref block );

};






#endif