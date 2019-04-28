#!/usr/bin/python
import xml.etree.ElementTree as ET
import sys

itemGroup = '''
<ItemGroup Label="resources_pipeline_output">
  <_CustomResource Include="..\..\..\\resources\common\**\*">
    <Link>resources\%(RecursiveDir)%(FileName)%(Extension)</Link>
    <DeploymentContent>true</DeploymentContent>
  </_CustomResource>
</ItemGroup>
'''

target = '''
<Target BeforeTargets="AssignTargetPaths" Name="_CollectCustomResources">
  <Message Text="Adding resource: %(_CustomResource.Identity) -&gt; %(_CustomResource.Link)" />
  <ItemGroup><None Include="@(_CustomResource)" /></ItemGroup>
</Target>
'''

def update_project_file(filename):
    ET.register_namespace('', 'http://schemas.microsoft.com/developer/msbuild/2003')
    tree = ET.parse(filename)
    root = tree.getroot()
    
    root.append(ET.XML(itemGroup))
    root.append(ET.XML(target))

    tree.write(filename)

if __name__ == '__main__':
    update_project_file(sys.argv[1])