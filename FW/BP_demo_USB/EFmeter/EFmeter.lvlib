﻿<?xml version='1.0' encoding='UTF-8'?>
<Library LVVersion="24008000">
	<Property Name="Instrument Driver" Type="Str">True</Property>
	<Property Name="NI.Lib.DefaultMenu" Type="Str">dir.mnu</Property>
	<Property Name="NI.Lib.Description" Type="Str">LabVIEW Plug and Play instrument driver for

&lt;fill in information about manufacturer, model, and type of the instrument&gt;.</Property>
	<Property Name="NI.Lib.Icon" Type="Bin">*!#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!(_!!!*Q(C=\&gt;4"=2J"%!81FMM(8]H!21K&gt;!CG11K@!V5&gt;3["2)A21["6,A[+P]7)V&gt;0EE8OWR6;6;.Y-`MT'.WW9CN@9HY(-^PN?_PNP@@([_WD`[0`P@&gt;`U9TZNO&lt;A`ZSCXD;J'J5KV+Z@&lt;PHE9^]Z#-@_=B&lt;XP+7N\TF,3^ZS5N?]J+80/5J4XH+5Z\S\:#(0/1BNSND]&lt;(1G(2--!;DR(A:HO%:HO(R-9:H?):H?)&lt;(E"C?Y2G?Y2E?J]8Q$-`Q$-`QG'K4T(&lt;)?9&lt;(^.%]T&gt;-]T&gt;-]FITG;9#W7*OY49)2L&lt;/^;:\G;2ZPIXG;JXG;JXFU2`-U4`-U4`-Y:&gt;O6XD301]ZDGCC?YCG?YCE?5U@R&amp;%`R&amp;%`R7#[+JXA+ICR9*E?)=F):5$Y54`(Y&amp;]640-640-7D;\N#N?X-1`-YZ$T*ETT*ETT*9YJ)HO2*HO2*(N.']C20]C20]FAKEC&gt;ZEC&gt;"UK+7DT2:/D%.3E(S_.POFNSO5G_3X)\VUXSZ570&gt;A,&amp;OL&amp;AX4+Q&lt;)&gt;9&amp;DH8B9FW17"M&gt;;Q.D&lt;5SM,RTLC]1#RFIYVI3R"M&lt;&gt;[UV&gt;V57&gt;V5E&gt;V5(NV?ZR[B]??,`@YX;\R@6[D=PF%O@T/5[H5RS0RTA=$L(@\W/XW`V[7HVVP,3HH]_F&lt;^\`CXJZ,PU0T]&lt;Y&amp;-_`0?&lt;NU1_[`-%`!!!!!!</Property>
	<Property Name="NI.Lib.SourceVersion" Type="Int">604012544</Property>
	<Property Name="NI.Lib.Version" Type="Str">1.0.0.0</Property>
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Item Name="Private" Type="Folder">
		<Property Name="NI.LibItem.Scope" Type="Int">2</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Item Name="Default Instrument Setup.vi" Type="VI" URL="../Private/Default Instrument Setup.vi"/>
	</Item>
	<Item Name="Public" Type="Folder">
		<Property Name="NI.LibItem.Scope" Type="Int">1</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Item Name="Action-Status" Type="Folder">
			<Item Name="Action-Status.mnu" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/Public/Action-Status/Action-Status.mnu"/>
		</Item>
		<Item Name="Configure" Type="Folder">
			<Item Name="Low Level" Type="Folder">
				<Item Name="Configure_Low Level.mnu" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/Public/Configure/Low Level/Configure_Low Level.mnu"/>
				<Item Name="Configure Multipoint.vi" Type="VI" URL="../Public/Configure/Low Level/Configure Multipoint.vi"/>
				<Item Name="Configure Trigger.vi" Type="VI" URL="../Public/Configure/Low Level/Configure Trigger.vi"/>
			</Item>
			<Item Name="Configure.mnu" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/Public/Configure/Configure.mnu"/>
			<Item Name="Configure Autozero.vi" Type="VI" URL="../Public/Configure/Configure Autozero.vi"/>
			<Item Name="Configure Measurement.vi" Type="VI" URL="../Public/Configure/Configure Measurement.vi"/>
		</Item>
		<Item Name="Data" Type="Folder">
			<Item Name="Low Level" Type="Folder">
				<Item Name="Data_Low Level.mnu" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/Public/Data/Low Level/Data_Low Level.mnu"/>
				<Item Name="Fetch Multiple Points.vi" Type="VI" URL="../Public/Data/Low Level/Fetch Multiple Points.vi"/>
				<Item Name="Initiate.vi" Type="VI" URL="../Public/Data/Low Level/Initiate.vi"/>
				<Item Name="Send Software Trigger.vi" Type="VI" URL="../Public/Data/Low Level/Send Software Trigger.vi"/>
			</Item>
			<Item Name="Data.mnu" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/Public/Data/Data.mnu"/>
			<Item Name="Read (Single Point).vi" Type="VI" URL="../Public/Data/Read (Single Point).vi"/>
			<Item Name="Read.vi" Type="VI" URL="../Public/Data/Read.vi"/>
		</Item>
		<Item Name="Utility" Type="Folder">
			<Item Name="Utility.mnu" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/Public/Utility/Utility.mnu"/>
			<Item Name="Error Query.vi" Type="VI" URL="../Public/Utility/Error Query.vi"/>
			<Item Name="Reset.vi" Type="VI" URL="../Public/Utility/Reset.vi"/>
			<Item Name="Revision Query.vi" Type="VI" URL="../Public/Utility/Revision Query.vi"/>
			<Item Name="Self-Test.vi" Type="VI" URL="../Public/Utility/Self-Test.vi"/>
			<Item Name="SetMode.vi" Type="VI" URL="../SetMode.vi"/>
		</Item>
		<Item Name="dir.mnu" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/Public/dir.mnu"/>
		<Item Name="Close.vi" Type="VI" URL="../Public/Close.vi"/>
		<Item Name="Initialize.vi" Type="VI" URL="../Public/Initialize.vi"/>
		<Item Name="VI Tree.vi" Type="VI" URL="../Public/VI Tree.vi"/>
	</Item>
	<Item Name="EFmeter Readme.html" Type="Document" URL="/&lt;instrlib&gt;/EFmeter/EFmeter Readme.html"/>
</Library>
