# GameEngineSandbox

![Azure pipeline badge](https://coderox.visualstudio.com/Game%20Engine%20Sandbox/_apis/build/status/Build%20master%20branch)

<ItemGroup Label="resource_pipeline_output">
    <_CustomResource Include="..\..\resources\**\*">
        <Link>resources\%(RecursiveDir)%(FileName)%(Extension)</Link>
        <DeploymentContent>true</DeploymentContent>
    </_CustomResource>
</ItemGroup>
<Target BeforeTargets="AssignTargetPaths" Name="_CollectCustomResources">
    <Message Text="Adding resource: %(_CustomResource.Identity) -&gt; %(_CustomResource.Link)" />
    <ItemGroup><None Include="@(_CustomResource)" /></ItemGroup>
</Target>
