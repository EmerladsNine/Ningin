using Microsoft.VisualStudio.Text;
using Microsoft.VisualStudio.Text.Classification;
using Microsoft.VisualStudio.Text.Tagging;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;

namespace NinginToolsExtension
{
    /// <summary>
    /// Classifier that classifies all text as an instance of the "NinginScene" classification type.
    /// </summary>
    internal class NinginScene : IClassifier
    {
        /// <summary>
        /// Classification type.
        /// </summary>
        private readonly IClassificationType classificationType;
        private readonly IClassificationType _IdentifierType;
        private readonly IClassificationType _HeadIdentifierType;
        private readonly IClassificationType _ChildIdentifierType;
        private readonly IClassificationType _TypeIdentifierType;
        private readonly IClassificationType _StringType;
        private readonly IClassificationType _BoolType;
        private readonly IClassificationType _NumberType;
        private readonly IClassificationType _commentType;


        /// <summary>
        /// Initializes a new instance of the <see cref="NinginScene"/> class.
        /// </summary>
        /// <param name="registry">Classification registry.</param>
        internal NinginScene(ITextBuffer buffer, IClassificationTypeRegistryService registry)
        {
            Debug.WriteLine("GetClassifier called for buffer: " + buffer);
            this.classificationType = registry.GetClassificationType("NinginScene");
            _IdentifierType = registry.GetClassificationType("NinginSceneIdentifier");
            _HeadIdentifierType = registry.GetClassificationType("NinginSceneHeadIdentifier");
            _ChildIdentifierType = registry.GetClassificationType("NinginSceneChildIdentifier");
            _TypeIdentifierType = registry.GetClassificationType("NinginSceneTypeIdentifier");
            _StringType = registry.GetClassificationType("NinginSceneString");
            _BoolType = registry.GetClassificationType("NinginSceneBool");
            _NumberType = registry.GetClassificationType("NinginSceneNumber");
            _commentType = registry.GetClassificationType("NinginSceneComment");
        }

        #region IClassifier

#pragma warning disable 67

        /// <summary>
        /// An event that occurs when the classification of a span of text has changed.
        /// </summary>
        /// <remarks>
        /// This event gets raised if a non-text change would affect the classification in some way,
        /// for example typing /* would cause the classification to change in C# without directly
        /// affecting the span.
        /// </remarks>
        public event EventHandler<ClassificationChangedEventArgs> ClassificationChanged;

#pragma warning restore 67

        /// <summary>
        /// Gets all the <see cref="ClassificationSpan"/> objects that intersect with the given range of text.
        /// </summary>
        /// <remarks>
        /// This method scans the given SnapshotSpan for potential matches for this classification.
        /// In this instance, it classifies everything and returns each span as a new ClassificationSpan.
        /// </remarks>
        /// <param name="span">The span currently being classified.</param>
        /// <returns>A list of ClassificationSpans that represent spans identified to be of this classification.</returns>
        public IList<ClassificationSpan> GetClassificationSpans(SnapshotSpan span)
        { 
            int tokenCount;
            IntPtr fileInputPtr = Marshal.StringToHGlobalAnsi(span.Snapshot.GetText());
            string text = span.Snapshot.GetText();

            IntPtr tokenPtr = RustCalls.getTokens(fileInputPtr, out tokenCount);

            Marshal.FreeHGlobal(fileInputPtr);

            if (tokenPtr == IntPtr.Zero)
            {
                Console.WriteLine("Error occurred while getting tokens.");
            }

            Token[] tokens = new Token[tokenCount];
            for (int i = 0; i < tokenCount; i++)
            {
                tokens[i] = Marshal.PtrToStructure<Token>(IntPtr.Add(tokenPtr, i * Marshal.SizeOf<Token>()));
            }

            var result2 = new List<ClassificationSpan>();
            for (int i = 0; i < tokenCount; i++)
            {
                IntPtr tokenType = tokens[i].token_type;
                if (tokenType == IntPtr.Zero)
                {
                    result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 1].start, tokens[i].start.ToInt32()).ToInt32())), this._IdentifierType));
                }
                else if (tokenType == new IntPtr(10))
                {
                    if (tokens[i + 1].token_type == IntPtr.Zero)
                    {
                        result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 2].start, tokens[i].start.ToInt32()).ToInt32())), this._HeadIdentifierType));
                        i++;
                    }
                }
                else if (tokenType == new IntPtr(11))
                {
                    if (tokens[i + 1].token_type == IntPtr.Zero)
                    {
                        result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 2].start, tokens[i].start.ToInt32()).ToInt32())), this._ChildIdentifierType));
                        i++;
                    }
                }
                else if (tokenType == new IntPtr(12))
                {
                    if (tokens[i + 1].token_type == IntPtr.Zero)
                    {
                        result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 2].start, tokens[i].start.ToInt32()).ToInt32())), this._TypeIdentifierType));
                        i++;
                    }
                }
                else if (tokenType == new IntPtr(1))
                {
                    result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 1].start, tokens[i].start.ToInt32()).ToInt32())), this._StringType));
                }
                else if (tokenType == new IntPtr(2))
                {
                    result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 1].start, tokens[i].start.ToInt32()).ToInt32())), this._BoolType));
                }
                else if (tokenType == new IntPtr(20) || tokenType == new IntPtr(21))
                {
                    result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 1].start, tokens[i].start.ToInt32()).ToInt32())), this._NumberType));
                }
                else if ( tokenType == new IntPtr(22) )
                {
                    result2.Add(new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(tokens[i].start.ToInt32(), IntPtr.Subtract(tokens[i + 1].start, tokens[i].start.ToInt32()).ToInt32())), this._commentType));
                }
            }
            return result2;
        }
        #endregion
    }
}
