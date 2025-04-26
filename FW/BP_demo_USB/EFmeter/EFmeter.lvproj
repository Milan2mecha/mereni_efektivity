<?xml version='1.0' encoding='UTF-8'?>
<Project Name="Template - DMM.lvproj" Type="Project" LVVersion="24008000" URL="/&lt;instrlib&gt;/_Template - DMM/Template - DMM.lvproj">
	<Property Name="Instrument Driver" Type="Str">True</Property>
	<Property Name="NI.Project.Description" Type="Str">This project is used by developers to edit API and example files for LabVIEW Plug and Play instrument drivers.</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="CCSymbols" Type="Str">OS,Win;CPU,x86;</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Examples" Type="Folder">
			<Item Name="DEMO.vi" Type="VI" URL="/&lt;instrlib&gt;/EFmeter/Examples/DEMO.vi"/>
		</Item>
		<Item Name="EFmeter.lvlib" Type="Library" URL="/&lt;instrlib&gt;/EFmeter/EFmeter.lvlib"/>
		<Item Name="SetMode.vi" Type="VI" URL="../Public/Configure/SetMode.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="subElapsedTime.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/subElapsedTime.vi"/>
				<Item Name="FormatTime String.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/FormatTime String.vi"/>
			</Item>
			<Item Name="instr.lib" Type="Folder">
				<Item Name="Read (Single Point).vi" Type="VI" URL="/&lt;instrlib&gt;/EFmeter/Public/Data/Read (Single Point).vi"/>
				<Item Name="SetMode.vi" Type="VI" URL="/&lt;instrlib&gt;/EFmeter/SetMode.vi"/>
				<Item Name="Initialize.vi" Type="VI" URL="/&lt;instrlib&gt;/EFmeter/Public/Initialize.vi"/>
			</Item>
			<Item Name="EFmeter.lvlib" Type="Library" URL="../EFmeter.lvlib"/>
			<Item Name="EFmeter.lvlib" Type="Library" URL="../Public/Configure/EFmeter.lvlib"/>
			<Item Name="Error Query.vi" Type="VI" URL="../Public/Configure/Public/Utility/Error Query.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
